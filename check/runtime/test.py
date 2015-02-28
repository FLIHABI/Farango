
# This file is part of Farango.
#
# Copyright (c) 2015 FLIHABI.
#
# Farango is licensed under the FLIHABI License Version 1.
#
# Farango is free software: you can redistribute it and/or modify it under
# the terms of the GNU Lesser General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option)
# any later version.
#
# In addition, 180 days after any changes are published, you can use the
# software, incorporating those changes, under the terms of the MIT license,
# as described in the FLIHABI License Version 1.
#
# Farango is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
# more details.
#
# You should have received a copy of the GNU Lesser General Public License,
# the MIT license and the FLIHABI License Version 1 along with this program.
# If not, see <http://www.gnu.org/licenses/> for the GNU Lesser General Public
# License and see <http://goo.gl/t8dfl6> for the full license, including
# the MIT license.

import os
import sys
import fnmatch

from argparse import ArgumentParser
from os import listdir
from os.path import join, realpath, dirname
from subprocess import Popen, PIPE
from contextlib import contextmanager
from colors import Color
from log import log, error, info, important

PATH = dirname(dirname(realpath(__file__)))
TESTS_PATH = join(PATH, 'tests')

sys.path.append(TESTS_PATH)

@contextmanager
def process(*args, **kwargs):
    timeout = kwargs['timeout']
    del kwargs['timeout']
    kwargs['stdin'] = kwargs['stdout'] = kwargs['stderr'] = PIPE
    proc = None
    try:
        proc = Popen(*args, **kwargs)
        proc.test_timeout = timeout
        yield proc
    finally:
        if proc is not None:
            proc.wait(timeout)


class TestInfo(object):

    def __init__(self, module):
        self.module = module

    def __getattr__(self, name):
        if hasattr(self.module, name):
            return getattr(self.module, name)
        else:
            return None


def get_info(categories, name):
    try:
        module = '.'.join(categories + [name])
        module = __import__(module)
        for node in categories[1:]:
            module = getattr(module, node)
        module = getattr(module, name)

        no_match_str = "%s do not match: \n\texpected: \"%s\"\n\tactual: \"%s\"\n"

        def compare_output(output, **kwargs):
            expected = getattr(module, 'output')
            result = expected == output
            return (result, "" if result else no_match_str % ("Outputs", expected, output))

        def compare_error(error, **kwargs):
            expected = getattr(module, 'error')
            result = expected == error
            return (result, "" if result else no_match_str % ("Error outputs", expected, error))

        def compare_exit_status(exit_status, **kwargs):
            expected = getattr(module, 'exit_status')
            result = expected == exit_status
            return (result, "" if result else no_match_str % ("Exit statuses", expected, exit_status))

        module.__dict__.setdefault('parameters', [])
        module.__dict__.setdefault('rules', ['compare_output', 'compare_error', 'compare_exit_status'])
        module.__dict__.setdefault('input', b'')
        module.__dict__.setdefault('output', b'')
        module.__dict__.setdefault('error', b'')
        module.__dict__.setdefault('exit_status', 0)
        module.__dict__.setdefault('timeout', 1)
        module.__dict__.setdefault('compare_output', compare_output)
        module.__dict__.setdefault('compare_error', compare_error)
        module.__dict__.setdefault('compare_exit_status', compare_exit_status)

        return TestInfo(module)
    except ImportError:
        raise


def category_name(categories):
    name = ''
    for category in categories[:-1]:
        name += category + '::'
    return name + categories[-1]


def run_test(binary, categories, name, timeout=None):
    test_info = get_info(categories, name)
    if timeout:
        test_info.timeout = timeout

    test_prefix = category_name(categories)
    print(Color.fg.green + '[ RUN      ]: %s::%s' % (test_prefix, name))

    proc = out = err = None
    with process([binary] + test_info.parameters, timeout=test_info.timeout) as proc:
        args = []
        if len(test_info.input) > 0:
            args += [test_info.input]
        out, err = map(lambda arr: arr.decode('latin-1'),
                proc.communicate(*args, timeout=proc.test_timeout))

    fail_string = []
    success = True

    for rule in test_info.rules:
        rule = getattr(test_info.module, rule)
        state, message = rule(output=out, error=err, exit_status=proc.returncode, time=0)
        success = success and state
        fail_string += [message]

    if success:
        print(Color.fg.green + '[       OK ]: %s::%s' % (test_prefix, name))
        return True
    else:
        print(Color.fg.red + '[     FAIL ]: %s::%s' % (test_prefix, name))
        for msg in fail_string:
            error(msg)
        return False


def fetch_tests():
    result = dict()
    node = result
    for root, dirnames, filenames in os.walk(TESTS_PATH):
        for filename in fnmatch.filter(filenames, '*.py'):
            path = dirname(join(root, filename)[len(TESTS_PATH) + 1:]).split('/')
            for category in path:
                if category not in node:
                    node[category] = dict()
                node = node[category]
            if '.' not in node:
                node['.'] = []
            node['.'].append('.'.join(filename.split('.')[:-1]))
            node = result
    return result


def walk_tests(path, node):
    for key, item in node.items():
        if type(item) is dict:
            for n in walk_tests(path + [key], item):
                yield n
        else:
            yield (path, item)
            for i in item:
                yield (path, i)
            yield (path, None)


def main(percent=False, timeout=None, binary=None):
    binary = join(dirname(PATH), binary)
    if not os.path.exists(binary):
        error(binary + ' does not exist: cannot run test suite.')
        return

    total_s = 0.0
    total_f = 0.0
    test_count = 0

    print(Color.fg.green + '[==========]')

    success = fail = 0.0
    local_test_count = 0
    for (categories, test) in walk_tests([], fetch_tests()):
        if type(test) is list:
            info('%s (%d tests)' % (category_name(categories), len(test)))
            local_test_count = len(test)
        elif test is None:
            ps = success / local_test_count * 100.0
            pf = fail / local_test_count * 100.0
            important('Summary -- %d%% succeeded, %d%% failed' % (ps, pf))

            test_count += local_test_count

            total_s += success
            total_f += fail
            success = fail = 0.0
            local_test_count = 0
        else:
            if run_test(binary, categories, test, timeout):
                success += 1
            else:
                fail += 1

    if test_count == 0:
        info('Nothing to be done.')
        return

    if not percent:
        important('Synthesis -- %d test%s, %d passed, %d failed.' % (
            test_count,
            ("s" if test_count != 1 else ""),
            total_s,
            total_f))
    else:
        ps = total_s / test_count * 100.0
        pf = total_f / test_count * 100.0
        important('Final %% summary -- %d %% succeeded, %d %% failed' % (ps, pf))


if __name__ == '__main__':
    parser = ArgumentParser()
    parser.add_argument('--binary')
    parser.add_argument('-p', '--percent', action='store_true')
    parser.add_argument('-t', '--timeout', nargs='?')
    main(**dict(vars(parser.parse_args())))
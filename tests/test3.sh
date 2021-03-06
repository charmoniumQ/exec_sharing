#!/usr/bin/env bash

set -e -x
cd $(dirname "$0")/..

log="$(mktemp)"
py_env="env PYTHONPATH=./cpython/Lib:./cpython/build/lib.linux-x86_64-3.9-pydebug LD_LIBRARY_PATH=./cpython PYTHONHOME=./cpython"

${py_env} ./src/exec_sharing.exe \
	src/run_python2.so           tests/test3.py   \;   \
	src/run_python2.so           tests/test3.py        \
	2>&1 | sort | tee "${log}"

	# src/run_python.so -c "$(cat tests/test3.py)" \

# same pid, different tid, same rand
test $(grep pid  "${log}" | uniq | wc -l) -eq 1
test $(grep tid  "${log}" | uniq | wc -l) -eq 2
test $(grep rand "${log}" | uniq | wc -l) -eq 1

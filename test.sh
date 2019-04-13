#!/bin/bash

ECHO='echo -e'
ERRONLY='2>&1 1>/dev/null'
OURS='./hsh'
OUTONLY='2>/dev/null'
THEIRS='sh'


check ()
{
	if [[ "$real_out" != "$our_out" ]]
	then
		echo Test: "$command"
		echo Expected Output: "${#real_out} bytes"
		echo "$real_out"
		echo
		echo Actual Output: "${#our_out} bytes"
		echo "$our_out"
	fi
	if [[ "$real_err" != "$our_err" ]]
	then
		echo Test: "$command"
		echo Expected Error: "${#real_err} bytes"
		echo "$real_err"
		echo
		echo Actual Error: "${#our_err} bytes"
		echo "$our_err"
	fi
}


runtest ()
{
	command="$1"
	trying="$ECHO '$command' | $THEIRS $OUTONLY"
	real_out="$(bash -c "$trying")"
	trying="$ECHO '$command' | $THEIRS $ERRONLY"
	real_err="$(bash -c "$trying")"
	trying="$ECHO '$command' | $OURS $OUTONLY"
	our_out="$(bash -c "$trying")"
	trying="$ECHO '$command' | $OURS $ERRONLY"
	our_err="$(bash -c "$trying")"
	check
	echo ----------------------------------------
}


runtest '/bin/ls'
runtest '/bin/ls\n/bin/ls'
runtest 'blah'
runtest 'cal'
runtest ' '

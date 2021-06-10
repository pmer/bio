#!/bin/sh
code=0
cd input
for name in *; do
    exe=../build/$name
    out=out-$name
    answer=../answers/$name

    if [ ! -x $exe ]; then
        continue
    fi

    printf "$name... "

    $exe >$out 2>&1
    rv=$?

    if [ $rv -ne 0 ]; then
        echo exitted with $rv
        cat $out
        code=1

    elif ! cmp $out $answer >/dev/null >&1; then
        echo differs
        echo '  answer file:'
        cat $answer
        echo '  program:'
        cat $out
        code=1

    else
        echo okay

    fi

    echo
    rm -f $out
done

exit $code

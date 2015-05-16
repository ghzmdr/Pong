DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

if [[ -a $DIR/bin/release ]]; then
	cd $DIR
	./bin/release 2>&1 /dev/null &
	echo "Pong Release launched!"
elif [[ -a $DIR/bin/debug ]]; then
	cd $DIR
	./bin/debug 2>&1 /dev/null &
	echo "Pong Debug launched!"
else echo "You have to compile/install the game first!"
fi

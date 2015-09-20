#!/bin/bash

rm -f _objs

echo -e "OBJSX = \\" >> _objs
find src -name "*.cpp" -printf "	\$(OBJECT_DIR)/%f \<newLine>" | sed 's/.cpp/\'$'.o/g' | sed 's/<newLine>/\'$'\n/g' >> _objs
echo -e -n "\n\n" >> _objs

echo -n "build_objs:" >> _objs
find src -name "*.cpp" -printf " \$(OBJECT_DIR)/%f" | sed 's/.cpp/\'$'.o/g' | sed 's/<newLine>/\'$'\n/g' >> _objs
echo -e -n "\n\n" >> _objs

find src -name "*.cpp" -printf "\$(OBJECT_DIR)/%fREMOVE: \$(SOURCE_DIR)/%P<newLine>	@\$(COMP) \$(CFLAGS) -c \$(SOURCE_DIR)/%P -o \$(OBJECT_DIR)/%fREMOVE \$(LIBS)<newLine>" | sed 's/.cppREMOVE/\'$'.o/g' | sed 's/<newLine>/\'$'\n/g' >> _objs

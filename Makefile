VERSION=0.3.0
NAME=line

CFLAGS=-Wall -D LINUX -std=c11 -I include -D LINE_VERSION=\"${VERSION}\" -D LINE_NAME=\"${NAME}\"
CC=gcc
PROGRAMM=line
SRC=src
OBJS=${BIN}/main_linux.o ${BIN}/window_linux.o ${BIN}/arg.o ${BIN}/sys_file.o ${BIN}/key_linux.o ${BIN}/monitor_linux.o ${BIN}/stringh.o ${BIN}/syntax.o ${BIN}/color.o ${BIN}/sys_linux.o ${BIN}/memfree.o ${BIN}/var.o ${BIN}/key_map.o ${BIN}/transcode.o ${BIN}/hexshow.o ${BIN}/utils.o
LIBS=-lncurses
BIN=bin

SRC_TEST=test
BIN_TEST=bin_test
TEST_PROGRAMM=line_test
OBJS_TEST=${BIN_TEST}/test_cases.o ${BIN_TEST}/test.o

all: ${PROGRAMM}
test: ${TEST_PROGRAMM}

debug: all
debug: CFLAGS=-D DEBUG -g -Wall -D LINUX -std=c11 -I include -D LINE_VERSION=\"${VERSION}\" -D LINE_NAME=\"${NAME}\"

debug_test: all_test
debug_test: CFLAGS=-D DEBUG -g -Wall -D LINUX -std=c11 -I include -D LINE_VERSION=\"${VERSION}\" -D LINE_NAME=\"${NAME}\"


${PROGRAMM}: ${BIN} ${OBJS}
	${CC} ${CFLAGS} -o $@ ${OBJS} ${LIBS}

${TEST_PROGRAMM}: ${BIN} ${OBJS} ${BIN_TEST} ${OBJS_TEST}
	${CC} ${CFLAGS} -o $@ ${BIN}/transcode.o ${OBJS_TEST}

${BIN}:
	mkdir $@

${BIN_TEST}:
	mkdir $@

${BIN}/%.o: ${SRC}/%.c
	${CC} ${CFLAGS} -c $< -o $@

${BIN_TEST}/%.o: ${SRC_TEST}/%.c
	${CC} ${CFLAGS} -c $< -o $@

.PHONY: clean all debug all_test debug_test

clean:
	rm -f ${OBJS_TEST_HEX}
	rm -rf ${BIN_TEST}
	rm -f ${OBJS}
	rm -rf ${BIN}
	rm -f ${TEST_PROGRAMM}
	rm -f ${PROGRAMM}

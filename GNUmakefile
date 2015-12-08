SRCS=		luamotif.c widgets.c constants.c
LIB=		motif

LUAVER=		`lua -v 2>&1 | cut -c 5-7`

CFLAGS+=	-Wall -O3 -fPIC -I/usr/include -I${PKGDIR}/include \
		-I/usr/include/lua${LUAVER}
LDADD+=		-L${XDIR}/lib -L${PKGDIR}/lib -lXm -lXt -lX11 -lbsd

PKGDIR=		/usr
LIBDIR=		${PKGDIR}/lib
LUADIR=		${LIBDIR}/lua/${LUAVER}
${LIB}.so:	${SRCS:.c=.o}
		cc -shared -o ${LIB}.so ${CFLAGS} ${SRCS:.c=.o} ${LDADD}

clean:
		rm -f *.o *.so
install:
	-mkdir -p ${DESTDIR}${LUADIR}
	install -m 755 ${LIB}.so ${DESTDIR}${LUADIR}/${LIB}.so

SRCS=		luamotif.c widgets.c constants.c
LIB=		motif

LUA=		$(shell lua${SUFFIX} -v 2>&1 | cut -d ' ' -f 1)
LUAIMPLVER=	$(shell lua${SUFFIX} -v 2>&1 | cut -d ' ' -f 2 | cut -c 1-3)

ifeq (${LUA},LuaJIT)
  LUAVER=	5.1
  LUAINCVER=	-${LUAIMPLVER}
  LUALIBVER=	-${LUAVER}
else
  LUAVER=	${LUAIMPLVER}
  LUAINCVER=	${LUAVER}
  LUALIBVER=	${LUAVER}
endif

CFLAGS+=	-Wall -O3 -fPIC -I/usr/include -I${PKGDIR}/include \
		-I/usr/include/lua${SUFFIX}${LUAINCVER}
LDADD+=		-L${XDIR}/lib -L${PKGDIR}/lib -llua${SUFFIX}${LUALIBVER} -lXm -lXt -lX11 -lbsd

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

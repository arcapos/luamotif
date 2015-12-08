SRCS=		luamotif.c widgets.c constants.c
LIB=		motif

OS!=		uname

OPENGL?=	no

.if ${OS} == "NetBSD"
XDIR=		${X11ROOTDIR}
LOCALBASE=	/usr/pkg
LDADD+=		-R/usr/lib -R${XDIR}/lib -R${LOCALBASE}/lib
.else
XDIR=		/usr/X11R6
LOCALBASE=	/usr/local
.endif

NOLINT=	1
CFLAGS+=	-I${XDIR}/include -I${LOCALBASE}/include
LDADD+=		-L${XDIR}/lib -L${LOCALBASE}/lib -lXm -lXext -lXt -lX11
.if ${OPENGL} == "yes"
CFLAGS+=	-DOPENGL
LDADD+=		-lGLw -lGLU -lGL
.endif

LIBDIR=		${LOCALBASE}/lib/lua/5.2

libinstall:

install:
	${INSTALL} -d ${DESTDIR}${LIBDIR}
	${INSTALL} lib${LIB}.so.${SHLIB_FULLVERSION} \
	    ${DESTDIR}${LIBDIR}/${LIB}.so

.include <bsd.lib.mk>

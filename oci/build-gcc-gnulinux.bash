### 

PICK_GCC_MVER="12"
PICK_GCC_FULLVER="12.3.0"
PICK_OS="deb10"
PICK_TARGET="${PICK_GCC_FULLVER}-${PICK_OS}-x86_64"
CTN_BUILD="build-gcc-$PICK_TARGET-container"
CTN_PACK="package-gcc-$PICK_TARGET-container"
PICK_BASEIMG="debian:buster-slim"
PXY_FRONTEND=""
APT_COUNTRY_CODE="us"

if [[ -v USE_PROXYCHAINS ]]
then
    PXY_FRONTEND="proxychains"
    echo "[INFO] using proxy frontend '$PXY_FRONTEND'"
fi

if [[ -v CURR_LOC ]]
then
    APT_COUNTRY_CODE=$CURR_LOC
    echo "[INFO] using country code '$APT_COUNTRY_CODE'"
fi


###

# skip building if already built
flag=$(buildah ps | grep $CTN_BUILD | wc -l)
test $flag -eq 0 || exit 0

buildah from --name $CTN_BUILD $PICK_BASEIMG

buildah run $CTN_BUILD -- \
	sed -i \
	"s/deb\.debian\.org/ftp\.$APT_COUNTRY_CODE\.debian\.org/" \
	/etc/apt/sources.list

buildah run $CTN_BUILD -- \
	apt-get -o Acquire::ForceIPv4=true update
buildah run $CTN_BUILD -- \
	apt-get -o Acquire::ForceIPv4=true install g++ make wget curl bzip2 autogen dejagnu -y --quiet

test $? -eq 0 || exit 2

$PXY_FRONTEND buildah run $CTN_BUILD -- \
	bash -c "wget https://ftp.gnu.org/gnu/gcc/gcc-${PICK_GCC_FULLVER}/gcc-${PICK_GCC_FULLVER}.tar.gz"

test $? -eq 0 || exit 3

buildah run $CTN_BUILD -- \
	bash -c "tar xf gcc-${PICK_GCC_FULLVER}.tar.gz"

test $? -eq 0 || exit 4

$PXY_FRONTEND buildah run $CTN_BUILD -- \
	bash -c "cd gcc-${PICK_GCC_FULLVER} && ./contrib/download_prerequisites"

test $? -eq 0 || exit 4

buildah run $CTN_BUILD -- \
	bash -c "mkdir objdir && cd objdir && ../${PICK_GCC_FULLVER}/configure --program-prefix='alt-' --disable-multilib --disable-libsanitizer --enable-languages=c,c++ --enable-shared=libgcc,libstdc++"

test $? -eq 0 || exit 4

# build 100min+ on 4C
buildah run $CTN_BUILD -- \
	bash -c 'cd objdir && make -j$(nproc)'

test $? -eq 0 || exit 4

# test 200min+ on 4C
# buildah run $CTN_BUILD -- \
#	bash -c 'cd objdir && make -j$(nproc) -k check'

test $? -eq 0 || exit 4

buildah run $CTN_BUILD -- \
	bash -c 'cd objdir && make install'

test $? -eq 0 || exit 4


# package

buildah from --name $CTN_PACK $PICK_BASEIMG
buildah copy --from $CTN_BUILD $CTN_PACK '/usr/local' '/usr/local'

test $? -eq 0 || exit 5

OCIIMG_NAME="gcc-voa"
OCIIMG_FULLNAME="localhost/$OCIIMG_NAME:$PICK_TARGET"

buildah commit $CTN_PACK $OCIIMG_FULLNAME

test $? -eq 0 || exit 5

podman save --output $OCIIMG_NAME.tar --format oci-archive $OCIIMG_FULLNAME

test $? -eq 0 || exit 5

podman inspect $OCIIMG_FULLNAME >$OCIIMG_NAME.json

test $? -eq 0 || exit 5

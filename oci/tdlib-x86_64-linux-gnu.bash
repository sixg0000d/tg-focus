### 

PICK_PLATFORM="x64-linux-gnu"
PICK_GCC_VER="12.3.0"
PICK_GCC_OS="deb10"
PICK_GCC_ARCH="x64"
IMGNAME_GCC="docker.io/micl2e2/gcc-voa:$PICK_GCC_VER-$PICK_GCC_OS-$PICK_GCC_ARCH"
CTN_TDLIB="build-tdlib-$PICK_PLATFORM-container"
CTN_PACK="package-tdlib-$PICK_PLATFORM-container"
CTN_GCC="package-gcc-$PICK_PLATFORM-container"
PICK_SRC="030e440757478ef5f5fdb01f60c3c6d885330c72"
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

buildah images | grep $IMGNAME_GCC
test $? -ne 0 || exit 1

buildah from --name $CTN_GCC $IMGNAME_GCC

test $? -eq 0 || exit 1


# skip building if already built
flag=$(buildah ps | grep $CTN_TDLIB | wc -l)
test $flag -eq 0 || exit 0

buildah from --name $CTN_TDLIB $PICK_BASEIMG

buildah run $CTN_TDLIB -- \
	sed -i \
	"s/deb\.debian\.org/ftp\.$APT_COUNTRY_CODE\.debian\.org/" \
	/etc/apt/sources.list

buildah run $CTN_TDLIB -- \
	apt-get -o Acquire::ForceIPv4=true update
buildah run $CTN_TDLIB -- \
	apt-get -o Acquire::ForceIPv4=true install gperf cmake g++ git zlib1g-dev libssl-dev wget -y --quiet

test $? -eq 0 || exit 2

$PXY_FRONTEND buildah run $CTN_TDLIB -- \
	bash -c "git clone https://github.com/tdlib/td"

test $? -eq 0 || exit 3

buildah run $CTN_TDLIB -- \
	bash -c "cd td && git reset --hard $PICK_SRC"

test $? -eq 0 || exit 4

# gcc
buildah copy --from $CTN_GCC $CTN_TDLIB '/usr/local' '/usr/local'

test $? -eq 0 || exit 4

buildah run $CTN_TDLIB -- \
	bash -c "cd td && mkdir -p build && cd build && cmake -DCMAKE_BUILD_TYPE=Release -DZLIB_LIBRARY=/usr/lib/x86_64-linux-gnu/libz.a  -DOPENSSL_USE_STATIC_LIBS=TRUE -DCMAKE_C_COMPILER=/usr/local/bin/alt-gcc -DCMAKE_CXX_COMPILER=/usr/local/bin/alt-g++ .."

test $? -eq 0 || exit 4

buildah run $CTN_TDLIB -- \
	bash -c 'cd td/build && LD_LIBRARY_PATH=/usr/local/lib64:$LD_LIBRARY_PATH make -j$(nproc)'

test $? -eq 0 || exit 4

buildah run $CTN_TDLIB -- \
	bash -c 'cd td/build && LD_LIBRARY_PATH=/usr/local/lib64:$LD_LIBRARY_PATH make test'

test $? -eq 0 || exit 4

buildah run $CTN_TDLIB -- \
	bash -c "cd td/build && LD_LIBRARY_PATH=/usr/local/lib64:$LD_LIBRARY_PATH make install"

test $? -eq 0 || exit 4

# package

buildah from --name $CTN_PACK $PICK_BASEIMG
buildah copy --from $CTN_TDLIB $CTN_PACK '/usr/local' '/usr/local'
buildah copy --from $CTN_GCC $CTN_PACK '/usr/local' '/usr/local'

PACK_IMGNAME="tdlib-$PICK_PLATFORM"
PACK_IMGTAG="$PICK_SRC"

buildah commit $CTN_PACK "$PACK_IMGNAME:$PACK_IMGTAG"

podman save --output $PACK_IMGNAME.tar --format oci-archive localhost/"$PACK_IMGNAME:$PACK_IMGTAG"

podman inspect localhost/"$PACK_IMGNAME:$PACK_IMGTAG" >$PACK_IMGNAME.json

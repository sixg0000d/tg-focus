###

PICK_PLATFORM="x64-linux-gnu"
PICK_TDLIB_SRC="030e440757478ef5f5fdb01f60c3c6d885330c72"
IMGNAMETAG_TDLIB="docker.io/micl2e2/gcc-voa-tdlib:$PICK_TDLIB_SRC-$PICK_PLATFORM"
CTN_TDLIB="package-tdlib-$PICK_PLATFORM-container"
CTN_TGFOCUS="build-tgfocus-$PICK_PLATFORM-container"
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

# prepare tdlib
buildah ps | grep $CTN_TDLIB
if [[ $? -ne 0 ]]
then
    buildah from --name $CTN_TDLIB $IMGNAMETAG_TDLIB
    test $? -eq 0 || exit 1
fi

# delete existing build
flag=$(buildah ps | grep $CTN_TGFOCUS | wc -l)
test $flag -eq 0 || buildah rm $CTN_TGFOCUS

buildah from --name $CTN_TGFOCUS $PICK_BASEIMG
test $? -eq 0 || exit 1

buildah copy --from $CTN_TDLIB $CTN_TGFOCUS '/usr/local' '/usr/local'
test $? -eq 0 || exit 1

buildah run $CTN_TGFOCUS -- \
	sed -i \
	"s/deb\.debian\.org/ftp\.$APT_COUNTRY_CODE\.debian\.org/" \
	/etc/apt/sources.list
buildah run $CTN_TGFOCUS -- \
	apt-get -o Acquire::ForceIPv4=true update
buildah run $CTN_TGFOCUS -- \
	apt-get -o Acquire::ForceIPv4=true \
	install \
	g++ git make cmake zlib1g-dev libssl-dev locales \
	-y --quiet

test $? -eq 0 || exit 2

$PXY_FRONTEND buildah run $CTN_TGFOCUS -- \
        git clone --depth=1 https://github.com/micl2e2/tg-focus

test $? -eq 0 || exit 3

$PXY_FRONTEND buildah run $CTN_TGFOCUS -- \
	bash -c "cd tg-focus && bash dev/install-deps-oci-only.bash"

test $? -eq 0 || exit 4

buildah run $CTN_TGFOCUS -- \
	bash -c "cd tg-focus && cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=/usr/local/bin/alt-gcc -DCMAKE_CXX_COMPILER=/usr/local/bin/alt-g++ -B build"
test $? -eq 0 || exit 5

buildah run $CTN_TGFOCUS -- \
	bash -c 'cd tg-focus/build && LD_LIBRARY_PATH=/usr/local/lib64:$LD_LIBRARY_PATH make -j$(nproc)'
test $? -eq 0 || exit 5

buildah run $CTN_TGFOCUS -- \
        bash -c 'sed -i "s/# en_US.UTF-8 UTF-8/en_US.UTF-8 UTF-8/" /etc/locale.gen'
test $? -eq 0 || exit 6

buildah run $CTN_TGFOCUS -- \
        locale-gen
test $? -eq 0 || exit 7

buildah run $CTN_TGFOCUS -- \
	bash -c 'cd tg-focus/build && LD_LIBRARY_PATH=/usr/local/lib64:$LD_LIBRARY_PATH make test'
test $? -eq 0 || exit 8

buildah run $CTN_TGFOCUS -- \
	bash -c "cd tg-focus && strip /tg-focus/build/tf-conf && strip /tg-focus/build/tf-focusd"
test $? -eq 0 || exit 9


# package

PACK_IMGNAME="localhost/tgfocus-$PICK_PLATFORM"

buildah commit $CTN_TGFOCUS $PACK_IMGNAME
test $? -eq 0 || exit 10

tmpctn=$(podman create $PACK_IMGNAME)
test $? -eq 0 || exit 11

artifacts_dir="tg-focus-$PICK_PLATFORM"
rm -rf $artifacts_dir
mkdir -p $artifacts_dir

podman cp $tmpctn:/tg-focus/build/tf-conf $artifacts_dir/tf-conf
test $? -eq 0 || exit 12
podman cp $tmpctn:/tg-focus/build/tf-focusd $artifacts_dir/tf-focusd
test $? -eq 0 || exit 12
sha512sum $artifacts_dir/tf-* > $artifacts_dir/checksums
test $? -eq 0 || exit 12
tar --create --gzip --file $artifacts_dir.tar.gz $artifacts_dir
test $? -eq 0 || exit 13

podman rm $tmpctn
test $? -eq 0 || exit 14




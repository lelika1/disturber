#!/usr/bin/env bash

echo Hello world
set -ex
set -o pipefail

source /opt/qt*/bin/qt*.sh

qmake CONFIG+=release

make -j$(nproc)

mkdir -p /build/bundle
mv LangLearn /build/bundle
cd /build

wget -c "https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage"
chmod a+x linuxdeployqt*.AppImage
./linuxdeployqt*.AppImage --appimage-extract

unset QTDIR; unset QT_PLUGIN_PATH ; unset LD_LIBRARY_PATH

squashfs-root/AppRun bundle/LangLearn -bundle-non-qt-libs
squashfs-root/AppRun bundle/LangLearn -appimage

export URL="$(curl --upload-file ./Application-x86_64.AppImage https://transfer.sh/LangLearn-git.$BITBUCKET_COMMIT-x86_64.AppImage)"
export BUILD_STATUS="{\"key\":\"doc\", \"state\":\"SUCCESSFUL\", \"name\":\"Documentation\", \"url\":\"${URL}\"}"

curl -H "Content-Type:application/json" -X POST --user "${BB_AUTH_STRING}" -d "${BUILD_STATUS}" "https://api.bitbucket.org/2.0/repositories/${BITBUCKET_REPO_OWNER}/${BITBUCKET_REPO_SLUG}/commit/${BITBUCKET_COMMIT}/statuses/build"
#!/usr/bin/env bash

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

ls -lah

curl -X POST "https://${BB_AUTH_STRING}@api.bitbucket.org/2.0/repositories/${BITBUCKET_REPO_OWNER}/${BITBUCKET_REPO_SLUG}/downloads" --form files=@"Application-x86_64.AppImage"

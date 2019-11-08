#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import re
from cpt.packager import ConanMultiPackager


class BuilderSettings(object):
    @property
    def username(self):
        """ Set taocpp as package's owner
        """
        return os.getenv("CONAN_USERNAME", "taocpp")

    @property
    def upload(self):
        """ Set taocpp repository to be used on upload
        """
        bintray_url = "https://api.bintray.com/conan/taocpp/public-conan"
        return os.getenv("CONAN_UPLOAD", bintray_url)

    @property
    def channel(self):
        """ Default conan channel
        """
        return os.getenv("CONAN_CHANNEL", "stable")

    @property
    def upload_only_when_tag(self):
        """ Only upload the package the branch is a tag
        """
        return os.getenv("CONAN_UPLOAD_ONLY_WHEN_TAG", True)

    @property
    def reference(self):
        """ Read project version from CMake file to create Conan referece
        """
        pattern = re.compile(r"project \(taocpp-sequences VERSION (\d+\.\d+\.\d+) LANGUAGES CXX\)")
        version = None
        with open('CMakeLists.txt') as file:
            for line in file:
                result = pattern.match(line)
                if result:
                    version = result.group(1)
        if not version:
            raise Exception("Could not find version in CMakeLists.txt")
        return os.getenv("CONAN_REFERENCE", "sequences/{}@{}/{}".format(version, self.username, self.channel))

if __name__ == "__main__":
    settings = BuilderSettings()
    builder = ConanMultiPackager(
        reference=settings.reference,
        username=settings.username,
        upload=settings.upload,
        channel=settings.channel,
        upload_only_when_tag=settings.upload_only_when_tag,
        test_folder=os.path.join(".conan", "test_package"))
    builder.add()
    builder.run()

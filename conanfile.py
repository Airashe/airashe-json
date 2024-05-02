from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
import re
import os

class airasheJsonRecipe(ConanFile):
    name = "airashe-json"
    package_type = "library"
    version = None

    # Optional metadata
    author = "airashe"
    url = "https://github.com/airashe/airashe-json"
    description = "A library to work with JSON"

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    # Exported sources
    exports_sources = "CMakeLists.txt", "src/*.cpp", "src/*.h*"

    # Call before everything to define version
    def init(self):
        try:
            path = os.path.join(self.recipe_folder, "CMakeLists.txt")
            with open(path, "r") as f:
                content = f.read()
                regexp = fr"{self.name} LANGUAGES CXX VERSION (.*)\)"
                version = re.search(regexp.encode(), content.encode()).group(1).decode()
                self.version = version
                pass
        except Exception as e:
            print(e)
            return

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["airashe-json"]

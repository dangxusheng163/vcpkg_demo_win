

# 安装基线
	..\..\vcpkg\vcpkg.exe x-update-baseline --add-initial-baseline

# 1 install depend 
	..\..\vcpkg\vcpkg.exe install --triplet x64-windows
	..\..\vcpkg\vcpkg.exe install --triplet x64-windows-static
	 
# 2 build
	cmake -B self_build -S . -G "Visual Studio 15 2017" -A x64 -DCMAKE_TOOLCHAIN_FILE="N:/vcpkg/scripts/buildsystems/vcpkg.cmake" -DCMAKE_INSTALL_PREFIX="self_build/install" -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="self_build/vcpkg_installed/x64-windows"
	cmake -B self_build -S . -G "Visual Studio 15 2017" -A x64 -DCMAKE_TOOLCHAIN_FILE="N:/vcpkg/scripts/buildsystems/vcpkg.cmake" -DCMAKE_INSTALL_PREFIX="self_build/install" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH="self_build/vcpkg_installed/x64-windows"

# 2 编译
	cmake --build self_build --config Release --target ALL_BUILD
	cmake --build self_build --config Release --target install
	cmake --build self_build --config Debug --target ALL_BUILD
	cmake --build self_build --config Debug --target install

# 3 run
	cd .\self_build\Release
	cd .\self_build\Debug
	.\vcpkg_test.exe
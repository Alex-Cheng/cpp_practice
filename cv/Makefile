.PHONY: build config run

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
depot := $(patsubst %/,%,$(dir $(mkfile_path)))

export CC := $(shell which clang-17)
export CXX := $(shell which clang++-17)
CMAKE_BUILD_TYPE ?= Debug

build_out := build-debug
ifeq ($(CMAKE_BUILD_TYPE),RelWithDebInfo)
build_out := build-relwithdeb
else ifeq ($(CMAKE_BUILD_TYPE),Release)
build_out := build-release
endif

export PATH := $(depot)/$(build_out)/programs:$(PATH)

.diagnostics:
	@echo depot: $(depot)
	@echo CC: $(CC)
	@echo CXX: $(CXX)
	@echo CMAKE_BUILD_TYPE: $(CMAKE_BUILD_TYPE)
	@echo build_out: $(build_out)

build: .diagnostics config
	cmake --build $(build_out)  

config: .diagnostics
	cmake -G Ninja \
		-DCMAKE_C_COMPILER=$(CC) \
		-DCMAKE_CXX_COMPILER=$(CXX) \
		-DCMAKE_ASM_COMPILER=$(CC) \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
		-DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) \
		-S . -B $(build_out)

run: build
	cd $(build_out) && \
	./cv

clean: .diagnostics
	@echo -n "Are you sure to delete $(build_out)? [y/N] " && read ans && if [ $${ans:-'N'} = 'y' ]; then rm -rf $(build_out); fi 

info: .diagnostics

from invoke import Context, task

NAME = "slither"
BUILD_DIR = "build"
TEST_BUILD_DIR = f"{BUILD_DIR}-test"


@task(help={"config": "The compiler configuration to use"})
def build(c: Context, config: str):
    c.run(
        f"cmake -DCMAKE_BUILD_TYPE={config.capitalize()} -B {BUILD_DIR}-{config} -S . -G Ninja"
    )
    c.run(f"cmake --build {BUILD_DIR}-{config} -j 4")


@task
def clean(c: Context):
    c.run(f"rm -rf ./{{{BUILD_DIR}-debug,{BUILD_DIR}-release,{TEST_BUILD_DIR}}}")


@task(help={"config": "The compiler configuration to use"})
def run(c: Context, config: str, gui: bool = False):
    exe = f"./{BUILD_DIR}-{config}/{NAME}"

    if gui:
        c.run(f"{exe} --gui")
    else:
        if (result := c.run(f"getcap {exe}")) != None and result.stdout == "":
            c.run(f"sudo setcap cap_dac_override=ep {exe}")

        c.run(f"{exe} --verbose")


@task
def test(c: Context):
    c.run(f"cmake -B {TEST_BUILD_DIR} -S ./test/")
    c.run(f"cmake --build {TEST_BUILD_DIR} -j 4")
    c.run(f"./{TEST_BUILD_DIR}/{NAME}_test")

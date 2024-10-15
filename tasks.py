from invoke import Context, Result, task

NAME = "slither"
BUILD_DIR = "build"
TEST_BUILD_DIR = f"{BUILD_DIR}_test"


@task
def build(c: Context):
    c.run(f"cmake -B {BUILD_DIR} -S . -G Ninja")
    c.run(f"cmake --build {BUILD_DIR} -j 4")


@task
def clean(c: Context):
    c.run(f"rm -rf ./{{{BUILD_DIR},{TEST_BUILD_DIR}}}")


@task
def run(c: Context):
    result: Result = c.run(f"getcap ./{BUILD_DIR}/{NAME}")
    if result.stdout == "":
        c.run(f"sudo setcap cap_dac_override=ep ./{BUILD_DIR}/{NAME}")

    c.run(f"./{BUILD_DIR}/{NAME} --verbose")


@task
def test(c: Context):
    c.run(f"cmake -B {TEST_BUILD_DIR} -S ./test/")
    c.run(f"cmake --build {TEST_BUILD_DIR} -j 4")
    c.run(f"./{TEST_BUILD_DIR}/{NAME}_test")

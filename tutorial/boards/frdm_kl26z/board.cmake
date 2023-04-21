# SPDX-License-Identifier: Apache-2.0

board_runner_args(jlink "--device=MKL26Z128xxx4")
board_runner_args(pyocd "--target=kl26z")

include(${ZEPHYR_BASE}/boards/common/pyocd.board.cmake)
include(${ZEPHYR_BASE}/boards/common/jlink.board.cmake)

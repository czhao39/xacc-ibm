/***********************************************************************************
 * Copyright (c) 2018, UT-Battelle
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the xacc nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Contributors:
 *   Initial implementation - H. Charles Zhao
 *
 **********************************************************************************/
#include <gtest/gtest.h>
#include "OpenQasmVisitor.hpp"
#include "OQASMCompiler.hpp"

using namespace xacc;

using namespace xacc::quantum;

TEST(OpenQasmCompilerTester, checkTeleportOQASM) {
    xacc::Initialize();

    const std::string src(
            "// quantum teleportation example\n"
            "OPENQASM 2.0;\n"
            "include \"qelib1.inc\";\n"
            "qreg q[3];\n"
            "creg c[3];\n"
            "// optional post-rotation for state tomography\n"
            "gate post q { }\n"
            "U(0.3,0.2,0.1) q[0];\n"
            "h q[1];\n"
            "cx q[1],q[2];\n"
            "barrier q;\n"
            "cx q[0],q[1];\n"
            "h q[0];\n"
            "measure q[0] -> c[0];\n"
            "measure q[1] -> c[1];\n"
            "post q[2];\n"
            "measure q[2] -> c[2];\n");

    auto compiler = std::make_shared<OQASMCompiler>();
    auto ir = compiler->compile(src);

    auto function = ir->getKernel("main");
    std::cout << "N: " << function->nInstructions() << "\n";

    EXPECT_TRUE(ir->getKernels().size() == 1);
}
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
#include <iostream>
#include <IRProvider.hpp>
#include <OQASM2BaseListener.h>

#include "OQASM2Lexer.h"

#include "XACC.hpp"
#include "OQASMCompiler.hpp"
#include "OQASMToXACCListener.hpp"


using namespace oqasm;
using namespace antlr4;


namespace xacc {

    namespace quantum {

        OQASMCompiler::OQASMCompiler() {
        }

        std::shared_ptr<IR> OQASMCompiler::compile(const std::string &src, std::shared_ptr<Accelerator> acc) {
            accelerator = acc;
            return compile(src);
        }

        std::shared_ptr<IR> OQASMCompiler::compile(const std::string &src) {
            auto ir = xacc::getService<IRProvider>("gate")->createIR();

            ANTLRInputStream input(src);
            OQASM2Lexer lexer(&input);
            CommonTokenStream tokens(&lexer);
            OQASM2Parser parser(&tokens);

            tree::ParseTree *tree = parser.mainprog();
            OQASMToXACCListener listener(ir);
            tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
        }
    }
}

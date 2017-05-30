/*
 * MIT License
 *
 * Copyright (c) 2017 Johannes Winkelmann
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <iostream>
#include <sstream>
#include <cmath>

#include "svggen.h"

#include "dial_dotsandnumbers.h"
#include "dial_circletests.h"
#include "dial_secondsat9.h"



int main(int argc, char** argv)
{
    SvgGen gen;

    double width = 120;
    double height = 120;

    gen.start(width, height, "mm");

    char sel = '0'; // default
    if (argc > 1) {
        sel = argv[1][0];
    }

    switch (sel) {
    case '1':
        dial_dotsAndNumbers(gen, 5, 5);
        break;
    case '2':
        dial_circleTests(gen, 5, 5);
        break;
    default:
        dial_secondsAt9(gen, 5, 5);
    }

    // bounding box
    // gen.rect(1, 1, width-1, height-1, "fill='transparent' stroke='#cccccc'");

    gen.end();

    std::cout << gen.str() << std::endl;
    return 0;
}

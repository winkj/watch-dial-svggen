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

#include <cmath>

#include "svggen.h"

void dial_circleTests(SvgGen& gen, double originX, double originY)
{
    std::string redCircleNoFill = "fill='#ffffff' stroke-width='1px' stroke='#ff0000'";
    std::string textStyle = "text-anchor='middle' alignment-baseline='central' font-size='8'";
    const char* labels[] = { "XII", "I", "II", "III", "IIII", "V", "VI", "VII", "VIII", "IX", "X", "XI" };

    double outerRadius = 50;

    originX += outerRadius;
    originY += outerRadius;

    double radiusStep = 10;

    double innerRadius = outerRadius - radiusStep;
    double miniRadius = innerRadius - radiusStep;
    double rectWidth = 2;
    double rectHeight = 4;
    double rectOffsetX = rectWidth / 2;
    double rectOffsetY = rectHeight / 2;
    double dotRadius = 2;

    double angleStep = 2 * 3.14159265359 / 12.0;
    double angleOffset = -3.14159265359 / 2;

    gen.circle(originX, originY, outerRadius, redCircleNoFill);
    gen.circle(originX, originY, innerRadius, redCircleNoFill);

    gen.circle(originX, originY, miniRadius+rectOffsetY, redCircleNoFill);
    gen.circle(originX, originY, miniRadius, redCircleNoFill);
    gen.circle(originX, originY, miniRadius-rectOffsetY, redCircleNoFill);


    for (int i = 0; i < 12; ++i) {
        // outer circle: dots
        double x = originX + outerRadius * cos(angleOffset +angleStep * i);
        double y = originY + outerRadius * sin(angleOffset +angleStep * i);
        gen.circle(x, y, dotRadius);

        // numbers
        x = originX + innerRadius * cos(angleOffset +angleStep * i);
        y = originY + innerRadius * sin(angleOffset +angleStep * i);
        gen.text(labels[i], x, y, textStyle);

        // outer circle: small rectangles, rotated
        x = originX + miniRadius * cos(angleOffset + angleStep * i);
        y = originY + miniRadius * sin(angleOffset + angleStep * i);
        gen.rect(x-rectOffsetX, y-rectOffsetY, rectWidth, rectHeight,
            "transform='rotate("
            + std::to_string(i * 30)
            + ", " + std::to_string(x)
            + ", " + std::to_string(y)
            + ")'"); // 30 = 360 / 12
    }
}

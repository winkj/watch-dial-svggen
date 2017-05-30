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

/**
 * a 38mm dial with seconds at 9am
 */
void dial_secondsAt9(SvgGen& gen, double originX, double originY)
{
    std::string redCircleNoFill = "fill='transparent' stroke-width='0.1mm' stroke='#ff0000'";
    std::string redCircleEngraveFill = "fill='#808080' stroke-width='0.0mm' stroke='#ff0000'";
    std::string redCircleWhiteFill = "fill='#ffffff' stroke-width='0.1mm' stroke='#ff0000'";
    std::string engraveFill = "fill='#808080'";

    double outerRadius = 19;

    originX += outerRadius;
    originY += outerRadius;

    double innerRadius = 17.5;
    double miniRadius = outerRadius - 4;

    // seconds mini dial
    double secondsOuterRadius = 6;
    double secondsMiddleRadius = 4.75;
    double secondsInnerRadius = 4;

    // decorative rects
    double rectWidth = 0.5;
    double rectHeight = 1;
    double rectOffsetX = rectWidth / 2;
    double rectOffsetY = rectHeight / 2;

    gen.circle(originX, originY, miniRadius, redCircleNoFill);
    gen.circle(originX-10.25, originY, secondsOuterRadius, redCircleWhiteFill);
    gen.circle(originX-10.25, originY, secondsInnerRadius, redCircleNoFill);
    gen.circle(originX, originY, outerRadius, redCircleWhiteFill + " mask='url(#cutoff)'");

    // mask out the inner circle; we can paint over the overlapping left part of the seconds, while keeping
    std::string mask = SvgGen().circle(originX, originY, miniRadius+0.2, "opacity='1'"); // +0.2 = 2x stroke; using a temp SvgGen since we don't wanna add it to our SVG
    gen.addDef("<mask id='cutoff'><rect id='bg' x='0' y='0' width='100%' height='100%' fill='white'/>" + mask + "</mask>");

    double angleStep = 2 * 3.14159265359 / 60.0;
    double angleOffset = -3.14159265359 / 2;

    for (int i = 0; i < 60; ++i) {
        rectHeight = (i % 5) ? 0.75 : 1.5;
        rectWidth = 0.5;

        double x = originX + innerRadius * cos(angleOffset + angleStep * i);
        double y = originY + innerRadius * sin(angleOffset + angleStep * i);
        gen.rect(x-rectOffsetX, y-rectOffsetY, rectWidth, rectHeight,
            "transform='rotate("
            + std::to_string(i * (360/60))
            + ", " + std::to_string(x)
            + ", " + std::to_string(y)
            + ")' " + engraveFill); // 30 = 360 / 60


        if (i % 5 == 0) {
            rectHeight = (i % 15 == 0) ? 1.5 : 1;
            rectWidth = (i % 15 == 0) ? 0.75 : 0.5;
            x = originX-10.25 + secondsMiddleRadius * cos(angleOffset + angleStep * i);
            y = originY + secondsMiddleRadius * sin(angleOffset + angleStep * i);

            gen.rect(x-rectOffsetX, y-rectOffsetY, rectWidth/2.0, rectHeight/2.0,
                "transform='rotate("
                + std::to_string(i * (360/60))
                + ", " + std::to_string(x)
                + ", " + std::to_string(y)
                + ")' " + engraveFill); // 30 = 360 / 60
            }
    }


    // 1mm tab for Ponoko
    // See http://support.ponoko.com/hc/en-us/community/posts/210090608-Metal-Machining-Starter-Kit-Inkscape
    originY -= outerRadius;
    rectWidth = 1;
    gen.rect(originX-(rectWidth/2), originY-(rectHeight/2), rectWidth, rectHeight, "fill='#ffffff'");


}

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

#ifndef _SVGGEN_H_
#define _SVGGEN_H_

class SvgGen
{
public:

    void start(double width, double height, std::string unit = "") {
        mHeader << "<svg version=\"1.1\"\n" \
            "\txmlns=\"http://www.w3.org/2000/svg\"\n" \
            "\txmlns:xlink=\"http://www.w3.org/1999/xlink\"\n" \
            "\twidth=\"" + std::to_string(width) + unit + "\"\n" \
            "\theight=\""+ std::to_string(height) + unit + "\"\n" \
            "viewBox=\"0 0 " + std::to_string(width) + " " + std::to_string(height) + "\">\n";
    }

    void end() {
        mData << "</svg>\n";
    }

    std::string circle(double cx, double cy, double r, const std::string& attr="") {
        Tag t("circle");
        t.addAttr("cx", cx);
        t.addAttr("cy", cy);
        t.addAttr("r", r);
        t.addAttrString(attr);
        mData << t.str() << "\n";
        return t.str();
    }

    void rect(double x, double y, double width, double height, const std::string& attr="") {
        Tag t("rect");
        t.addAttr("x", x);
        t.addAttr("y", y);
        t.addAttr("width", width);
        t.addAttr("height", height);
        t.addAttrString(attr);
        mData << t.str() << "\n";
    }

    void text(const std::string& text, double x, double y, const std::string& attr="") {
        Tag t("text");
        t.addAttr("x", x);
        t.addAttr("y", y);
        t.addValue(text);
        t.addAttrString(attr);
        mData << t.str() << "\n";
    }

    void addDef(const std::string& def) {
        std::string s{def};
        replace(s.begin(), s.end(), '\'', '\"' );
        mDefs << s << "\n";
    }

    std::string str() {
        mHeader << "<defs>\n" << mDefs.str() << "</defs>\n";
        return mHeader.str() + mData.str();
    }
private:

    class Tag {
    public:
        Tag(const std::string& name) : mName(name), mText("") {}

        std::string str() {
            std::string s = "<" + mName + " " + mData.str();
            if (mText == "") {
                s += "/>";
            } else {
                s += ">" + mText + "</" + mName + ">";
            }
            return s;
        }

        void addAttr(const std::string& name, double value) {
            addAttr(name, std::to_string(value));
        }

        void addAttr(const std::string& name, const std::string& value) {
            mData << name << "=\"" << value << "\" ";
        }

        void addAttrString(const std::string& s) {
            std::string t{s};
            replace(t.begin(), t.end(), '\'', '\"' );
            mData << t << " ";
        }

        void addValue(const std::string text) {
            mText = text;
        }

    private:
        std::stringstream mData;
        std::string mName;
        std::string mText;
    };

    std::stringstream mHeader;
    std::stringstream mData;
    std::stringstream mDefs;

};

#endif /* _SVGGEN_H_ */

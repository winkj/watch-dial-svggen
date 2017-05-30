# A simple SVG generator hack to generate watch dials.

## Purpose

I've been playing with SVG watch dials recently, and needed a tool to simplify
trying out ideas. I wrote this as a quick tool to programmatically generate
dials. It's by no means a complete svg generator

## Notes

1. The opening svg tag uses a viewbox; this makes sure that numbers without unit are considered to be in the unit that can optionally be speficied in `SvgGen::start()`
2. you can specify masks and clip path using `SvgGen::rect()`
3. passing arguments allows to select the dial generated
4. Since I was getting lazy escaping double quotes in attributes, I'm replacing single quotes to double quotes. *Note:* there's no way to avoid it
5. For the number four, I'm using "IIII" instead of the roman numeral "IV"; this is common for watches, see [here](http://www.orientalwatchsite.com/the-watchmakers-four-why-some-watches-use-iiii-instead-of-iv/)
6. `SvgGen` is implemented as a header only class, as it is fairly small; it could be split up to reduce compilation time if this becomes a problem

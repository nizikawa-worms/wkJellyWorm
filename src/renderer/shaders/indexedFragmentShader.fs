R"(
#version 130

out uint fragColor;

uniform usampler2D indexed_text;

void main() {
	uint palette_index = texture(indexed_text, gl_TexCoord[0].st).r;
	fragColor = palette_index;
}
)"
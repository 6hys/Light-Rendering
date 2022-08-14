#version 150

precision mediump float;

in vec4 vertexColor;          // This is the color from the vertex shader interpolated across the
                               // triangle per fragment.
 
out vec4 outputColor;

// The entry point for our fragment shader.
void main()
{
    outputColor = vertexColor;    // Pass the color directly through the pipeline.
}
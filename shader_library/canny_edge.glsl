// https://docs.opencv.org/4.x/da/d22/tutorial_py_canny.html
// https://automaticaddison.com/how-the-sobel-operator-works/

#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D u_texture; // input texture
uniform vec2 u_resolution;   // resolution of the screen or texture
uniform float u_threshold;   // threshold for edge detection

void main() {
    vec2 texCoord = gl_FragCoord.xy / u_resolution;

    // Sobel kernels for edge detection (approximating gradients)
    float kernelX[9];
    float kernelY[9];
    kernelX[0] = -1.0; kernelX[1] = 0.0; kernelX[2] = 1.0;
    kernelX[3] = -2.0; kernelX[4] = 0.0; kernelX[5] = 2.0;
    kernelX[6] = -1.0; kernelX[7] = 0.0; kernelX[8] = 1.0;

    kernelY[0] = -1.0; kernelY[1] = -2.0; kernelY[2] = -1.0;
    kernelY[3] =  0.0; kernelY[4] =  0.0; kernelY[5] =  0.0;
    kernelY[6] =  1.0; kernelY[7] =  2.0; kernelY[8] =  1.0;

    float Gx = 0.0;
    float Gy = 0.0;
    int index = 0;

    // Offsets for the 3x3 kernel
    for(int y = -1; y <= 1; y++) {
        for(int x = -1; x <= 1; x++) {
            vec2 offset = vec2(float(x), float(y)) / u_resolution;
            vec4 sample = texture2D(u_texture, texCoord + offset);
            float intensity = dot(sample.rgb, vec3(0.299, 0.587, 0.114)); // grayscale conversion
            Gx += intensity * kernelX[index];
            Gy += intensity * kernelY[index];
            index++;
        }
    }

    // Magnitude of gradient (edge strength)
    float edgeStrength = sqrt(Gx * Gx + Gy * Gy);

    // Apply threshold
    float edge = edgeStrength > u_threshold ? 1.0 : 0.0;

    // Output edge map
    gl_FragColor = vec4(vec3(edge), 1.0);
}

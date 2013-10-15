#version 330 core

uniform float X = 0.5;
uniform float Y = 0.5;

vec3 OutputColor;


vec2 multiply(vec2 fac1, vec2 fac2) {
	vec2 fac3 = vec2(fac1[0]*fac2[0]-fac1[1]*fac2[1], fac1[1]*fac2[0]+fac1[0]*fac2[1]);
	return fac3;
}

vec3 fractal (vec2 location, int iterations){
	float outerBounds = 250.0; 
	int i = 0;
	float distance;
	vec2 escape = location;
	while (i < iterations) {
		escape = multiply(escape, escape)/2+vec2(X, Y);
		distance = sqrt(escape[0]*escape[0]+escape[1]*escape[1]);

		if (distance>outerBounds) {
			/*float dist2color = sin(log2(log2(distance)/log2(2))/log2(2)*6.2831853071)/2+0.5;
			float vecComponent = 0.0;
			if (dist2color <= 1.0 && dist2color >= 0.0) {
				return vec3(dist2color, dist2color, dist2color);
			}
			else {return vec3(1.0,0.5,0.4);}*/
			float iterToColor = 1.0 - sqrt(i/(iterations * 1.0));
			return vec3(iterToColor, iterToColor, iterToColor);
		}
		i++;
	}
	return vec3(0.0, 0.0, 0.0);
}


void main(void) {
	OutputColor = fractal (vec2((gl_FragCoord.x-960)/300, (gl_FragCoord.y-540)/300), 150);
	gl_FragColor = vec4(OutputColor ,0.0);
}

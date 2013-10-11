#version 330 core

uniform float X = 0.5;
uniform float Y = 0.5;

vec3 OutputColor;

vec2 multiply(vec2 fac1, vec2 fac2) {
	vec2 fac3 = vec2(fac1[0]*fac2[0]-fac1[1]*fac2[1], fac1[1]*fac2[0]+fac1[0]*fac2[1]);
	return fac3;
}

vec3 fractal (vec2 location, int iterations){
	int i = 0;
	float distance;
	vec2 escape = location;
	while (i < iterations) {
		escape = multiply(escape, escape)/2+vec2((gl_FragCoord.x-960)/300, (gl_FragCoord.y-540)/300);
		distance = sqrt(escape[0]*escape[0]+escape[1]*escape[1]);
		if (distance>1000) {
			return vec3(	(cos(log2(distance/1000)*2/3)/2+0.5), 
					(cos(log2(distance/1000)*2/3)/2+0.5), 
					(cos(log2(distance/1000)*2/3)/2+0.5));
		}
		i++;
	}
	if (distance<1) {
		return vec3(0.0, 0.0, 0.0);
	}
}


void main(void) {
	OutputColor = fractal (vec2(X, Y), 100);
	gl_FragColor = vec4(OutputColor ,0.0);
}
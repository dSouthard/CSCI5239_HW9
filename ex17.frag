/*
 * CSCI 5239 Spring 2016
 * Diana Southard
 * 
 * Particle Engine: Fire Generator Shader
 *
 * Uses 2d Simplex noise from ex17
 * 
 */

uniform vec2 resolution;
uniform float time;
uniform float speed;
uniform float trans;

mat2 m = mat2(0.9,0.11,-0.7,1.0);

float hash (float n) {
	return fract(sin(n)*758.5453);
}

float noise (vec3 x ) {
	vec3 p = floor (x);
	vec3 f = fract(x);
	
	float n = p.x + p.y*57.0 + p.z*800.0;
	float mix1a = mix(hash(n+0.0), hash(n+1.0), f.x);
	float mix1b = mix(hash(n+57.0), hash(n+58.0), f.x);
	float mix2a = mix(hash(n+800.0), hash(n+801.0), f.x);
	float mix2b = mix(hash(n+857.0), hash(n+858.0), f.x);
	float mix1 = mix(mix1a, mix1b, f.y);
	float mix2 = mix(mix2a, mix2b, f.y);
	float res = mix(mix1, mix2, f.z);
	return res;
}

float fbm ( vec3 p) {
	float total = 0.0;
	total += 0.5*noise (p);
	p *= 2.02;
	
	total -= 0.25*noise (p);
	p *= 2.03;
	
	total += 0.125*noise (p);
	p *= 2.01;
	
	total += 0.0625*noise (p);
	p *= 2.04;
	
	total -= 0.03125*noise (p);
	
	return total/0.984375;
}

float cloud (vec3 p) {
	p -= fbm(vec3(p.x,p.y,0.0)*0.5)*2.25;
	
	float a = 0.0;
	a -= fbm(p*3.0)*2.2-1.1;
	
	if (a < 0.0) a = 0.0;
	a *= a;
	return a;
}

vec3 f2(vec3 c ) {
	c += hash(gl_FragCoord.x + gl_FragCoord.y*9.9)*0.01;
	 c *= 0.7-length(gl_FragCoord.xy/resolution.xy-0.5)*0.7;
	 float w = length(c);
	 c = mix(c*vec3(1.0, 1.0, 1.6), vec3(w,w,w)*vec3(1.4,1.2,1.0),w*1.1-0.2);
	 return c;
}
void main() {

	vec2 position = (gl_FragCoord.xy/resolution.xy );
	position.y += 0.2;
	
	vec2 coord = vec2((position.x-0.5)/position.y, 1.0/(position.y+0.2));
	
	coord += time*speed;
	
	float q = cloud(vec3(coord*1.0, 0.222));
	
	vec3 col = vec3(0.2,0.7,0.8) + vec3(q*vec3(0.2,0.4,0.1));
	
	gl_FragColor = vec4(f2(col), 1.0);
}

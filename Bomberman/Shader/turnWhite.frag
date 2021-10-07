precision mediump float;

uniform vec2 resolution;
uniform float time;

mat2 rot(float r)
{
  float s = sin(r);
  float c = cos(r);
  return mat2(c,s,-s,c);
}

const float pi = 3.141592;

vec2 pmod(vec2 p, float r)
{
  float a = atan(p.x,p.y)+pi/r;
  float n = pi*2./r;
  a = floor(a/n) * n;
  return p*rot(-a);
}
vec3 twist(vec3 p, float power){
    float s = sin(power * p.z);
    float c = cos(power * p.z);
    mat3 m = mat3(
          c,   s, 0.0,
         -s,   c, 0.0,
        0.0, 0.0, 1.0
    );
    return m * p;
}

float cube(vec3 p, vec3 s)
{
  vec3 q = abs(p) - s;
  float d = max(max(q.x,q.y),q.z);

  return d;
}

float map(vec3 p)
{
  vec3 q = p;
  q = twist(q,cos(time));
  q.z += time*2.+4.*abs(sin(time*2.));
  q.z = mod(q.z,2.) - 1.;
  float d;

  float r = 1.;
  for(int i = 0; i <13; i++)
  {

    q.xy = pmod(q.xy,r);
    q.xy = abs(q.xy) -1.5;

    d = cube(q,vec3(.55));
    d = min(d,1e5);

    r += 0.1;
  }

  return d;
}

void main()
{
  time *= 0.01;
  vec2 p = (gl_FragCoord.xy * 2. - resolution.xy) / min(resolution.x,resolution.y);

  //camera
  vec3 cPos = vec3(0.,0.,5.);
  vec3 cTar = vec3(0.);
  vec3 cDir = normalize(vec3(cTar-cPos));
  vec3 cUp = vec3(0.,1.,0.);
  vec3 cSide = cross(cDir,cUp);
  float targetDepth = 1.;

  //ray
  vec3 ray = normalize(p.x * cSide + p.y * cUp + cDir * targetDepth);

  //color
  vec3 color = vec3(0.);;
  float fogDist =0.;

  //raymarching
  float dist = 0.;
  float rLen = 0.;
  vec3 rPos = cPos;
  for(int i = 0; i < 32; i++)
  {
    dist = map(rPos);

    fogDist += dist;
    if(dist < 0.001)
    {
      break;
    }
    rLen += dist;
    rPos = cPos + rLen * ray;
  }


  color = vec3(1.,1.,1.);
  gl_FragColor = vec4(color*exp(-fogDist*fogDist*0.01),1.);


}

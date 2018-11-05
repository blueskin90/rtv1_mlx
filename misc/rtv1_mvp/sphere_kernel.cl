typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
}				t_vector;

__kernel void sphere(__global t_vector V, __global double *R)
{
	double order = sqrt(V.x * V.x + V.y * V.y + V.z + V.z);
	V.x = V.x / order;
	V.y = V.y / order;
	V.z = V.z / order;
}

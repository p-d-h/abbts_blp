#ifndef _PTT_H_
#define _PTT_H_
#define size_of_array 5000

class PTT {
public:
	float       rX;
	float       rY;
	float       rK;
	float		rTt;  // Totzeit

    PTT(void);
	PTT(float rK, float rTt);
	~PTT(void);
	void setup(void);
	void reset(void);
	float cyclic(float rX);

private:
    float arX[size_of_array];
	int iN;
	int ii;
};

# endif

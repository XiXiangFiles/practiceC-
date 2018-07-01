#include<iostream>
#include<stdio.h>
#include<stdlib.h>
class shape{
	protected:
		int width;
		int height;
	public:
		shape(int width,int height){
			this->width=width;
			this->height=height;
		}
		void getValue(){
			printf("%d\t%d\n",this->width,this->height);
		}
};
class triangle : public shape{
	public :
		triangle(int width,int height):shape(width,height){
				
		}
		int area(){
			return (width*height)/2;
		}
};
int main(void){
	triangle *t=new triangle(10,11);
	t->getValue();
	printf("area = %d\n",t->area());
	delete t;	
	return 0;
}

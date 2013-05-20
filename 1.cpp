int F(int i)
{
	if (i == 1)
		return 1;
	return F(i - 1) * i;
}
int main(){
    int score[6] = {76, 82, 90, 86, 79, 62};
    int credit[6] = {2, 2, 1, 2, 2, 3};
    int stu_number;
    int mean;
    int sum;
    int temp;
    int number;
    int i = 0;
	char a[] = {"please input your student number:\n"};	


while(1)
{
	printf("请输入数字：\n");
	scanf("%d",&number);
	temp = F(number);
	printf("%d的阶乘为：%d\n",number,temp);
    printf("%s",a);
    scanf("%d",&stu_number);

   sum = 0;
   temp = 0;
    
    for( i = 0; i < 6; i++)
    {
    
         sum = sum + score[i] * credit[i];
         temp = temp + credit[i];
    }
    mean = sum / temp;

    if(mean >= 60){
         mean = mean - 60;
         printf("the score of student number %d is %d higher than 60.\n", stu_number, mean);
    }
    else{
         mean = 60 - mean;
         printf("the score of student number %d is %d lower than 60.\n",stu_number, mean);
    }
}
    return 0;
}

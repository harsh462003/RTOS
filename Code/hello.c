#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>

MODULE_LICENSE("Dual BSD/GPL");

static int __init hello_init(void)
{
	int arr[10]={1,6,5,4,2,3,9,8,10,0};
	int i,j,temp;
	for(i=0;i<9;i++)
	{
		for(j=i+1;j<10;j++)
		{
			if(arr[i]>arr[j])
			{
				temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
			}
		}
	}
	printk(KERN_ALERT "Sorted array is");
	for(i=0;i<10;i++)
	   {
      		printk(KERN_ALERT "%i ",arr[i]);
	   }
	printk(KERN_ALERT "%i ",arr[9]);
	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);

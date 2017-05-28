/**
 * @file	cmpe283.c
 * @author	Akshay Sonvane
 * @date	20 May 2017
 * @version	0.5
 * @brief	Test module for new hypercalls
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("BSD");
MODULE_AUTHOR("Akshay Sonvane");
MODULE_DESCRIPTION("Test module for new hypercalls");
MODULE_VERSION("0.5");

#define NEWCPUID(func, subfunc, eax, ebx, ecx, edx) \
	asm __volatile("rolq $0x20, %%rax\norq $0x0F3B, %%rax\nvmcall" : \
	    "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx) : \
	    "a" (func), "c" (subfunc))

#define NEWCPUID2(func, subfunc, eax, ebx, ecx, edx) \
	asm __volatile("rolq $0x20, %%rax\norq $0x0F3C, %%rax\nvmcall" : \
	    "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx) : \
	    "a" (func), "c" (subfunc))

#define GETCTR(func, subfunc, eax, ebx, ecx, edx) \
	asm __volatile("rolq $0x20, %%rax\norq $0x0F3D, %%rax\nvmcall" : \
	    "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx) : \
	    "a" (func), "c" (subfunc))



/** @brief Test function for "NEWCPUID" hypercall
 */
static void test_newcpuid(void)
{
	uint32_t eax, ebx, ecx, edx;

	printk(KERN_INFO "%s: ----Testing NEWCPUID\n", __func__);
	
	/* Test function 0 */
	NEWCPUID(0, 0, eax, ebx, ecx, edx);
	printk(KERN_INFO "%s:  Function 0:\n", __func__);
	printk(KERN_INFO "%s:   %%eax=0x%x\n", __func__, eax);
	printk(KERN_INFO "%s:   %%ebx=0x%x\n", __func__, ebx);
	printk(KERN_INFO "%s:   %%ecx=0x%x\n", __func__, ecx);
	printk(KERN_INFO "%s:   %%edx=0x%x\n", __func__, edx);
}

static void test_newcpuid2(void)
{
	uint32_t eax, ebx, ecx, edx;

	printk(KERN_INFO "%s: ----Testing NEWCPUID2\n", __func__);
	
	/* Test function 0 with 0xA*/
	NEWCPUID2(0xA0000000, 0, eax, ebx, ecx, edx);
	printk(KERN_INFO "%s:  Function 0:\n", __func__);
	printk(KERN_INFO "%s:   %%eax=0x%x\n", __func__, eax);
	printk(KERN_INFO "%s:   %%ebx=0x%x\n", __func__, ebx);
	printk(KERN_INFO "%s:   %%ecx=0x%x\n", __func__, ecx);
	printk(KERN_INFO "%s:   %%edx=0x%x\n", __func__, edx);

	/* Test function 1 without 0xA*/
	NEWCPUID2(0, 0, eax, ebx, ecx, edx);
	printk(KERN_INFO "%s:  Function 0:\n", __func__);
	printk(KERN_INFO "%s:   %%eax=0x%x\n", __func__, eax);
	printk(KERN_INFO "%s:   %%ebx=0x%x\n", __func__, ebx);
	printk(KERN_INFO "%s:   %%ecx=0x%x\n", __func__, ecx);
	printk(KERN_INFO "%s:   %%edx=0x%x\n", __func__, edx);

}

static void test_getctr(void)
{
	uint32_t eax, ebx, ecx, edx;

	unsigned long i = 0; 
	printk(KERN_INFO "%s: ----Testing GETCTR\n", __func__);

	for(i=0; i<0xFFFFFFFE; i++){
	
	/* Test function 0 */
	GETCTR(0, 0, eax, ebx, ecx, edx);
	}
	/* Test function 1 */
	GETCTR(0, 0, eax, ebx, ecx, edx);
	printk(KERN_INFO "%s:  Function 0:\n", __func__);
	printk(KERN_INFO "%s:   %%eax=0x%x\n", __func__, eax);
	printk(KERN_INFO "%s:   %%ebx=0x%x\n", __func__, ebx);
	printk(KERN_INFO "%s:   %%ecx=0x%x\n", __func__, ecx);
	printk(KERN_INFO "%s:   %%edx=0x%x\n", __func__, edx);

	/* Test function 2 */
	GETCTR(0, 0, eax, ebx, ecx, edx);
	printk(KERN_INFO "%s:  Function 0:\n", __func__);
	printk(KERN_INFO "%s:   %%eax=0x%x\n", __func__, eax);
	printk(KERN_INFO "%s:   %%ebx=0x%x\n", __func__, ebx);
	printk(KERN_INFO "%s:   %%ecx=0x%x\n", __func__, ecx);
	printk(KERN_INFO "%s:   %%edx=0x%x\n", __func__, edx);


}


/** @brief Module initialization function
 *  @return 0 if successful
 */
static int __init cmpe283_init(void)
{
	printk(KERN_INFO "%s: Entering CMPE283 test module\n",
	    __func__);

	test_newcpuid();
	test_newcpuid2();
	test_getctr();

	return 0;
}

/** @brief Module cleanup function
 */
static void __exit cmpe283_exit(void)
{
	printk(KERN_INFO "%s: Exiting CMPE283 test module\n",
	    __func__);
}

/** @brief Identification of the module init and exit routines
 */
module_init(cmpe283_init);
module_exit(cmpe283_exit);

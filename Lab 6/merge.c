#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include <string.h>
#include <math.h>

void copy_arr (struct student* dest , int start , struct student* source , int lower , int upper)
{
	int i = 0 ;
	
	for ( ; lower <= upper ; lower++)
	{
		dest[start + i] = source[lower] ;
		i++ ;
	}
}

void copy_stu (struct student* dest , struct student *source)
{
	strcpy (dest->name , source->name) ;
	dest->cgpa = source->cgpa ;
}

void merge (struct student *s1 , int sz1 , struct student *s2 , int sz2 , struct student *dest)
{
	int i , s1_index , s2_index ;

	s1_index = s2_index = 0 ;

	for (i = 0 ; i < sz1 + sz2 ; i++)
	{
		if (s1_index >= sz1)
		{
			copy_stu (dest + i , s2 + s2_index) ;
			s2_index++ ;
		}
		else if (s2_index >= sz2)
		{
			copy_stu (dest + i , s1 + s1_index) ;
			s1_index++ ;
		}
		else 
		{
			if (s1[s1_index].cgpa < s2[s2_index].cgpa)
			{
				copy_stu (dest + i , s1 + s1_index) ;
				s1_index++ ;
			}
			else
			{
				copy_stu (dest + i , s2 + s2_index) ;
				s2_index++ ;
			}
		}
	}
}

void merge_sort (struct student *A , int size)
{
	if (size == 1)
		return ;

	int mid ;
	struct student *left, *right ;
	
	mid = size/2 ;
	if (size % 2 == 0)
	{
		left = (struct student*) malloc (mid * sizeof(struct student)) ;
		right = (struct student*) malloc (mid * sizeof(struct student)) ;

		copy_arr (left , 0 , A , 0 , mid-1) ;
		copy_arr (right , 0 ,  A , mid , size-1) ;

		/*

		printf ("Left unsorted- \n") ;		
		display_all_records (left , mid) ;
		printf ("Right unsorted - \n") ;
		display_all_records (right , mid) ;
		
		*/

		merge_sort (left , mid) ;
		merge_sort (right , mid) ;
		merge (left , mid , right , mid , A) ;

		/*

		printf ("Left - \n") ;
		display_all_records (left , mid) ;
		printf ("Right - \n") ;
		display_all_records (right , mid) ;
		printf ("Merged - \n") ;
		display_all_records (A , 2*mid) ;
		enter () ;

		*/
	}
	else
	{
		left = (struct student*) malloc (mid * sizeof(struct student)) ;
		right = (struct student*) malloc ((size - mid) * sizeof(struct student)) ;

		copy_arr (left , 0 , A , 0 , mid-1) ;
		copy_arr (right , 0 , A , mid , size-1) ;

		/*		
		printf ("Left unsorted- \n") ;		
		display_all_records (left , mid) ;
		printf ("Right unsorted - \n") ;
		display_all_records (right , size - mid) ; */

		merge_sort (left , mid) ;
		merge_sort (right , (size-mid)) ;
		merge (left , mid , right , size-mid , A) ;

		/*		
		printf ("Left sorted- \n") ;		
		display_all_records (left , mid) ;
		printf ("Right sorted - \n") ;
		display_all_records (right , size - mid) ;
		printf ("Merged - \n") ;
		display_all_records (A,size) ;
		enter () ;
		*/
	}	

	free (left) ;
	free (right) ;
}

int findmaxgrp (int size)
{
	int maxgrp ;

	maxgrp = 1 ;
	while (maxgrp < size)
		maxgrp *= 2 ;

	maxgrp /= 2 ;

	return maxgrp ;
}

void iter_merge_sort (struct student *A , int size)
{
	int i , grp , maxgrp ;
	int *first , *second, *merged ;

	grp = 1 ;
	maxgrp = findmaxgrp (size) ;

	while (grp <= maxgrp)
	{

		for (i = 0 ; i < size ; i += (grp*2))
		{	
			if (i + grp >= size)	//no second
			{
				continue ;
			}
			else if (i + 2*grp >= size)		//incomplete second
			{
				first = (struct student *) malloc (grp * sizeof(struct student)) ;
				second = (struct student *) malloc ((size - grp - i) * sizeof(struct student)) ;
				merged = (struct student *) malloc ((size - i) * sizeof(struct student)) ;

				copy_arr (first , 0 , A , i , i + grp - 1) ;
				copy_arr (second, 0 , A , i + grp , size - 1) ;
				merge (first , grp , second , size - grp - i , merged) ;
				copy_arr (A , i , merged , 0 , size - i - 1) ;

			}
			else			//normal case
			{
				first = (struct student *) malloc (grp * sizeof(struct student)) ;
				second = (struct student *) malloc (grp * sizeof(struct student)) ;
				merged = (struct student *) malloc (2 * grp * sizeof(struct student)) ;

				copy_arr (first , 0 , A , i , i + grp - 1) ;
				copy_arr (second , 0 , A , i + grp , i + 2*grp - 1) ;
				merge (first , grp , second , grp , merged) ;
				copy_arr (A , i , merged , 0 , 2*grp - 1) ;
			}

			free (first) ;
			free (second) ;
			free (merged) ;
		}	

		grp *= 2 ;
	}
}


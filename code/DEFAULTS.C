#include "defaults.h"

void set_defaults( void )
{
	int loop; 
	extern short col1;
	extern short col2;
	extern short col3;
	extern int old_resolution;
		
	for(loop=0;loop<10;loop++)
	{

		resolutions[loop].rows=25;
		resolutions[loop].columns=80;
		resolutions[loop].progs_win=11;
		resolutions[loop].other_win=3; 
		resolutions[loop].progs_win_width=2;	
		resolutions[loop].accs_win_width=3; 

	}
		resolutions[0].columns=40;

	prog_defaults.resolution=Getrez();
/*	prog_defaults.*/old_resolution=prog_defaults.resolution;
	col1=Setcolor(1,0x0000);
	col2=Setcolor(2,0x0000);
	col3=Setcolor(3,0x0000);
	
	

	if(prog_defaults.resolution>9)
	{
		BELL
		printf("WARNING A: Resolution greater than 9 found\n");
		printf("using number 9 slot, better inform the ST\n");
		printf("community\n");
		BELL
		prog_defaults.resolution=9;
	}

	if(prog_defaults.resolution==0 /* && prog_defaults.medium_res==1 */)
	{
		Setscreen((void *)-1,(void *)-1,(short)1);
		prog_defaults.resolution=1;
	}

	prog_defaults.rows=resolutions[prog_defaults.resolution].rows;
	prog_defaults.columns=resolutions[prog_defaults.resolution].columns;
	prog_defaults.progs_win=resolutions[prog_defaults.resolution].progs_win;
	prog_defaults.other_win=resolutions[prog_defaults.resolution].other_win;
	prog_defaults.progs_win_width=resolutions[prog_defaults.resolution].progs_win_width;
	prog_defaults.accs_win_width=resolutions[prog_defaults.resolution].accs_win_width;


	prog_defaults.bypass_time=10;

	prog_defaults.new_progs_flag=2;	/* 1 = ON, 2 = OFF, 3 = SAME */
	prog_defaults.new_accs_flag=2;
	prog_defaults.auto_paging=PAGING;		/* 1 = paging, 2 = scrolling */
	prog_defaults.accs_paging=PAGING;
	prog_defaults.sets_paging=PAGING;
	prog_defaults.other_paging=PAGING;
	prog_defaults.mouse_keys=0;



	prog_defaults.bypass_key_high=3866624;	/* F1 */
	prog_defaults.bypass_key_low=0x00;
	strcpy( prog_defaults.auto_path , "C:\\AUTO" );
	strcpy( prog_defaults.accs_path , "C:\\" );

	/* KEYS */

	prog_defaults.bypass_key_shift=0; 	/* F1 */
	prog_defaults.bypass_key_high=59; 	/* F1 */
	prog_defaults.bypass_key_low=0;
	strcpy(prog_defaults.bypass_key_text,"F1");

	prog_defaults.abort_key_shift=0;			/* ESC */
	prog_defaults.abort_key_high=1;			/* ESC */
	prog_defaults.abort_key_low=27;
	strcpy(prog_defaults.abort_key_text,"ESC");

	prog_defaults.page_key_shift=4;		/* CONTROL P */
	prog_defaults.page_key_high=25;		/* CONTROL P */
	prog_defaults.page_key_low=16;
	strcpy(prog_defaults.page_key_text,"CTL P");

	prog_defaults.toggle_key_shift=0;		/* SPACE */
	prog_defaults.toggle_key_high=57;		/* SPACE */
	prog_defaults.toggle_key_low=32;
	strcpy(prog_defaults.toggle_key_text,"SPACE");

	prog_defaults.switch_key_shift=0;		/* TAB */
	prog_defaults.switch_key_high=15;		/* TAB */
	prog_defaults.switch_key_low=9;
	strcpy(prog_defaults.switch_key_text,"TAB");

	prog_defaults.help_key_shift=0;		/* HELP */
	prog_defaults.help_key_high=98;		/* HELP */
	prog_defaults.help_key_low=0;
	strcpy(prog_defaults.help_key_text,"HELP");

	prog_defaults.options_key_shift=4;	/* CNTRL O */
	prog_defaults.options_key_high=24;	/* CNTRL O */
	prog_defaults.options_key_low=15;
	strcpy(prog_defaults.options_key_text,"CTL O");

	prog_defaults.new_key_shift=0;			/* INS */
	prog_defaults.new_key_high=82;			/* INS */
	prog_defaults.new_key_low=0;
	strcpy(prog_defaults.new_key_text,"INS");

	prog_defaults.delete_key_shift=0;		/* DELETE */
	prog_defaults.delete_key_high=83;		/* DELETE */
	prog_defaults.delete_key_low=127;
	strcpy(prog_defaults.delete_key_text,"DEL");


	top_line_size=1;				/*title line*/
	top_gap=0;				   	/* gap between title and windows */
	mid_window_titles=2;			/* titles of windows */
	mid_window_bottom=1;			/* bottom */
	middle_gap=0;				/* gap between that and the other window*/
	bot_window_title=1;
	bot_window_bottom=1;
	bottom_gap=0;
	bottom_line_size=2;			/* size of bottom lines */

	left_border=0;
	right_border=0;
	auto_accs_gap=0;
	accs_sets_gap=0;

}
			
void calculate_screen_sizes( void )
{

	int total_lines_used;
	int screen_lines_used;
	int defaults_lines_used;
	int gaps;
	int total_cols_used;

re_check_height:

	screen_lines_used=top_line_size+		/*title line*/
						top_gap+				   	/* gap between title and windows */
						mid_window_titles+		/* titles of windows */
				mid_window_bottom+			/* bottom */
				middle_gap+				/* gap between that and the other window*/
				bot_window_title+
				bot_window_bottom+
				bottom_gap+
				bottom_line_size;			/* size of bottom lines */	
	
	defaults_lines_used=	prog_defaults.progs_win+	/* size of progs win without titles etc */
								prog_defaults.other_win; /* size of other win without titles etc */

	total_lines_used=screen_lines_used + defaults_lines_used;
	extra_lines=prog_defaults.rows-total_lines_used;

	if(extra_lines != 0) /* gonna have to strip or pad */
	{
		/* first check for valid window sizes */
		if(prog_defaults.progs_win<=0)
			{
				prog_defaults.progs_win=1;
				goto re_check_height;
			}

		if(prog_defaults.other_win<=0)
			{
				prog_defaults.other_win=1;
				goto re_check_height;
			}

		if(extra_lines > 0) /* gonna have to pad */
		{

			gaps=extra_lines;

			/* increase the gaps */
			while(gaps!=0)
			{
				if(gaps>=3)
				{
					bottom_gap++;
					middle_gap++;
					top_gap++;
					gaps-=3;
				}
				else
				{
					if(gaps==2)
					{
						bottom_gap++;
						top_gap++;
						gaps-=2;
					}
					else		/* gaps is 1 */
					{
						middle_gap++;
						gaps-=1;
					}
				}
			}
						
		}
		else
		if(extra_lines < 0) /* gonna have to strip */
		{
			gaps=extra_lines*-1;
	
			
			/* gaps means gaps needed, so first off reduce the gaps */ 
			while(gaps!=0 &&( bottom_gap !=0 || middle_gap!=0 || top_gap!=0))
			{
				if(gaps>=3)
				{
					if(bottom_gap>0)
						{
						gaps--;
						bottom_gap--;
						}
					if(middle_gap>0)
						{
						gaps--;
						middle_gap--;
						}
					if(top_gap>0)
						{
						gaps--;
						top_gap--;
						}
				}
				else
				{
					if(gaps==2)
					{
						if(bottom_gap>0)
							{
							gaps--;
							bottom_gap--;
							}
						if(top_gap>0)
							{
							gaps--;
							top_gap--;
							}
						if(bottom_gap==0 && top_gap==0)
							{
								middle_gap--;
								gaps--;
							}	
					}
					else		/* gaps is 1 */
					{
						if(middle_gap>0)
							{
							middle_gap--;
							gaps--;
							}
						if(middle_gap==0)
							{
							if(bottom_gap>0)
								{
								gaps--;
								bottom_gap--;
								}
							if(top_gap>0)
								{
								gaps--;
								top_gap--;
								}
							}
					}
				}
			}

			if(gaps!=0)		/* need to make more gaps */
			{
				/* reduce the windows sizes */

				while(gaps!=0)
				{
					if((prog_defaults.progs_win%3)>prog_defaults.other_win)
					{
						prog_defaults.progs_win--;
						gaps--;
					}
					else
					{
						prog_defaults.other_win--;
						gaps--;
					}
				}
	
			}
		}
	}


	title_row=0;
	mid_window_title_row=top_line_size+top_gap;
	mid_window_first_item_row=mid_window_title_row+mid_window_titles;
	other_window_title_row=	mid_window_first_item_row+
									prog_defaults.progs_win+
									mid_window_bottom+
									middle_gap;
	other_window_first_item_row=other_window_title_row+
										bot_window_title;
	bottom_title_row=other_window_first_item_row+
							prog_defaults.other_win+
							bot_window_bottom+
							bottom_gap;

/*
printf("TITLE ROW %d\n",title_row);
printf("Top gap %d\n",top_gap);
printf("middle gap %d\n",middle_gap);
printf("bottom gap %d\n",bottom_gap);
printf("mid window title %d\n",mid_window_title_row);
printf("other window title ROW %d\n",other_window_title_row);
printf("bottom TITLE ROW %d\n",bottom_title_row);
getchar();
*/



/* now the widths and gaps calculations */

re_check_width:

	total_cols_used=((prog_defaults.progs_win_width*(PROG_NAME_SIZE+ARROW_BORDER))+ARROW_BORDER+(LINE_BORDER*2))+
						((prog_defaults.accs_win_width*(PROG_NAME_SIZE+ARROW_BORDER))+ARROW_BORDER+(LINE_BORDER*2))+
						 (SETS_NAME_SIZE+((ARROW_BORDER+LINE_BORDER)*2));

	gaps=prog_defaults.columns-total_cols_used;

	if(gaps!=0)		/* need to expand or contract */
	{
		if(gaps>0)	/* the easy one, need to expand */
		{
			while(gaps!=0)
			{
				if(gaps>=4)
				{
					left_border++;
					right_border++;
					auto_accs_gap++;
					accs_sets_gap++;
					gaps-=4;
				}
				else
				{
					if(gaps==3)
					{
						left_border++;
						right_border++;
						accs_sets_gap++;	
						gaps-=3;	
					}
					else
					{
						if(gaps==2)
						{
							auto_accs_gap++;
							accs_sets_gap++;
							gaps-=2;
						}
						else
						{
							accs_sets_gap++;
							gaps--;
						}
					}
				}
			}
		}
		else			/* the toughie, need to contract */
		{

			gaps=gaps*-1;

			/* leave for now */
			while(gaps!=0	&& (accs_sets_gap!=0 || left_border!=0 ||
									 right_border!=0 || auto_accs_gap!=0))
			{
				if(gaps>=4)
				{
					if(left_border>0)
						{
						gaps--;
						left_border--;
						}
					if(right_border>0)
						{
						gaps--;
						right_border--;
						}
					if(auto_accs_gap>0)
						{
						gaps--;
						auto_accs_gap--;
						}
					if(accs_sets_gap>0)
						{
						gaps--;
						accs_sets_gap--;
						}
				}
				else
				{
					if(gaps==3)
					{
					if(left_border>0)
						{
						gaps--;
						left_border--;
						}
					if(right_border)
						{
						gaps--;
						right_border--;
						}
					if(accs_sets_gap)
						{
						gaps--;
						accs_sets_gap--;
						}
					if(left_border==0 && right_border==0 && accs_sets_gap==0)
						{
						gaps--;
						auto_accs_gap--;
						}
					}
					else
					{
						if(gaps==2)
						{
							if(auto_accs_gap>0)
								{
									gaps--;
									auto_accs_gap--;
								}
							if(accs_sets_gap>0)
								{
									gaps--;
									accs_sets_gap--;
								}
							if(accs_sets_gap==0 && auto_accs_gap==0)
								{
									if(left_border>0)
									{
										gaps--;
										left_border--;
									}
									if(right_border>0)
									{
										gaps--;
										right_border--;
									}
								}

						}
						else
						{
							if(accs_sets_gap>0)
								{
									gaps--;
									accs_sets_gap--;
								}
							else
								{
									if(left_border>0)
										{
											gaps--;
											left_border--;
										}
									if(right_border>0)
										{
											gaps--;
											right_border--;
										}
									if(auto_accs_gap>0)
										{
											gaps--;
											auto_accs_gap--;
										}
								}
						}
					}
				}
			}

			if(gaps!=0)		/* oh no, gonna have to reduce sizes of windows */
			{
				if(prog_defaults.accs_win_width>1)
					{
						prog_defaults.accs_win_width--;		
						goto re_check_width;
					}
				if(prog_defaults.progs_win_width>1)
					{
						prog_defaults.progs_win_width--;		
						goto re_check_width;
					}

			}

		}
	}

	auto_menu_col=left_border;
	accs_menu_col=auto_menu_col+
					(prog_defaults.progs_win_width*(PROG_NAME_SIZE+ARROW_BORDER))+ARROW_BORDER+
					LINE_BORDER+
					LINE_BORDER+
					auto_accs_gap;
	sets_menu_col=accs_menu_col+
					(prog_defaults.accs_win_width*(PROG_NAME_SIZE+ARROW_BORDER))+ARROW_BORDER+
					LINE_BORDER+
					LINE_BORDER+
					accs_sets_gap;


	line_buffer=(char *)malloc(prog_defaults.columns+10);

}





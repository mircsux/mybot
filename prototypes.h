/* Function Prototypes */

int		get_random_number	(int);
int		main				(int, char **);
int		recv_data			(int, char *);
int		send_data			(int, char *);
char	* readln				(int, char *);
void	sig_alrm			(int);
void	sig_hup				(int);
void	sig_segv			(int);

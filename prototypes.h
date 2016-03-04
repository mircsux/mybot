/* Function Prototypes */

int		create_connection 	(char *, char *, long);
int		get_random_number	(int);
int		main				(int, char **);
int		recv_data			(int, char *);
int		send_data			(int, char *);
int		writeln				(const char *);

char	*	readln			(int, char *);

void	prepare_bot			();
void	sig_alrm			(int);
void	sig_hup				(int);
void	sig_segv			(int);

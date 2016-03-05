/* Function Prototypes */

int		create_connection 		(char *, char *, long);
int		get_random_number		(int);
int		main					(int, char **);
int		recv_data				(int, char *);
int		send_data				(int, char *);
int		writeln					(const char *);
int		readln 					(int);

int		register_bot			();
int		get_sendq_count 		(long);
int		Snow 					(const char *, ...);

void    clear_sendq 			(long, long);
void	S 						(const char *, ...);
void	del_sendq 				(long);
void	parse					(char *);
void	parse_ping				(char *);
void	parse_server_message	(int, char *, fd_set *);
void	prepare_bot				();
void	sig_alrm				(int);
void	sig_hup					(int);
void	sig_segv				(int);
void	stripline 				(char *);

extern	long	CONNECT_WAIT_TIMEOUT;

extern	char	HOSTNAME		[512];
extern	char	VHOST			[512];
extern	char	myline			[STRING_SHORT];
extern	int		alarmed;
extern	int		sockfd;
extern	int		PORT;
extern  int		send_tog;
extern	int		SEND_DELAY;

extern	struct sendq
{
        char data[STRING_SHORT];
        struct sendq *next;
}		*sendqhead, *sendqtail;


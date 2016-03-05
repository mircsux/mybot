/* Function Prototypes */

int		create_connection 		(char *, char *, long);
int		get_random_number		(int);
int		main					(int, char **);
int		recv_data				(int, char *);
int		Send 					(void);
int		send_data				(int, char *);
int		writeln					(const char *);
int		readln 					(void);
int		try_server_command		(char *, char *);

int		register_bot			();
int		get_sendq_count 		(long);
int		Snow 					(const char *format, ...);
int		stricmp 				(const char *, const char *);

void    clear_sendq 			(long, long);
void	S 						(const char *format, ...);
void	del_sendq 				(long);
void	parse					(char *);
void	parse_mode				(char *, char *);
void	parse_ping				(char *, char *);
void	parse_privmsg			(char *, char *);
void	parse_server_message	(fd_set *);
void	prepare_bot				();
void	sig_alrm				(int);
void	sig_hup					(int);
void	sig_segv				(int);
void	stripline 				(char *);

extern	long	CONNECT_WAIT_TIMEOUT;
extern	long	AIL666;
extern	long	AIL8;

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


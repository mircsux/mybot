/* Function Prototypes */

int		create_connection 		(char *, char *, long);
int		set_config_opt			(int, char *);
int		get_random_number		(int);
int		main					(int, char **);
int		recv_data				(int, char *);
int		Send 					(void);
int		send_data				(int, char *);
int		writeln					(const char *);
int		readln 					(void);
int		try_server_command		(int, char *, char *, char *);

int		register_bot			(void);
int		get_sendq_count 		(long);
int		Snow 					(const char *, ...);
int		stricmp 				(const char *, const char *);

void    clear_sendq 			(long, long);
void	S 						(const char *, ...);
void	do_add_servers			(char *);
void	add_iul_user			(char *, char *, char *, long);
void	add_isl_server 			(char *);
void	del_iul_user 			(const char *, char *);
void	del_sendq 				(long);
void	load_config				(char *);
void	parse					(char *);
void	parse_001				(int, char *, char *, char *);
void	parse_error				(int, char *, char *, char *);
void	parse_end_of_who		(int, char *, char *, char *);
void	parse_join				(int, char *, char *, char *);
void	parse_kick				(int, char *, char *, char *);
void	parse_mode				(int, char *, char *, char *);
void	parse_nick				(int, char *, char *, char *);
void	parse_part				(int, char *, char *, char *);
void	parse_ping				(int, char *, char *, char *);
void	parse_privmsg			(int, char *, char *, char *);
void	parse_who				(int, char *, char *, char *);
void	parse_server_message	(fd_set *);
void	prepare_bot				(void);
void	sig_alrm				(int);
void	sig_hup					(int);
void	sig_segv				(int);
void	stripline 				(char *);

extern	long	CONNECT_WAIT_TIMEOUT;
extern	long	AIL666;
extern	long	AIL8;

extern	char	HOSTNAME		[STRING_SHORT];
extern	char	VHOST			[STRING_SHORT];
extern	char	MYNICK			[STRING_SHORT];
extern	char	myline			[STRING_SHORT];
extern	int		alarmed;
extern	int		sockfd;
extern	int		PORT;
extern  int		send_tog;
extern	int		SEND_DELAY;
extern 	int		BurstingWho;

extern	struct sendq
{
        char data[STRING_SHORT];
        struct sendq *next;
}		*sendqhead, *sendqtail;

/* Internal Server List */
struct 		ISL	
{
		char		server 	[STRING_SHORT];
		char		chans 	[STRING_LONG];
		long		port;
		char		pass	[STRING_SHORT];
		int			sockfd;
		struct		ISL		*next;
		
}  *islhead;

/* Internal User List */
struct		IUL
{
	char	chan		[STRING_SHORT]; /* User's channel */
	char	nick		[STRING_SHORT]; /* User's nickname */
	char	uh			[STRING_SHORT]; /* User's hostmask */
	int		level;						/* Level user authed, if authed */
	long	idle;
	struct	IUL *next;
}   *iulhead;

typedef	struct	config_struct	{
	char	BOTNICK 		[STRING_SHORT];		/* My nickname */
	char	BOTCHAN			[STRING_LONG];		/* My channels */
	char	BOTUSER			[STRING_SHORT];		/* My username */
	char	BOTNAME			[STRING_SHORT];		/* My IRCNAME */
	char	BOTSERV			[STRING_LONG];		/* My servers/ports/pass */
	long	REJOIN_ON_KICK;						/* Rejoin on kick? */
} Config;

extern	Config *config;

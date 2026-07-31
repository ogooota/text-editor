#include <terminal/terminal.h>

#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

static struct termios original_terminal;
static bool raw_mode_enabled = false;

bool
terminal_get_dimensions(
    uint16_t *width,
    uint16_t *height
    )
{
  struct winsize w;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) < 0)
    return false;

  *width = (uint16_t)w.ws_col;
  *height = (uint16_t)w.ws_row;

  return true;
}

void
terminal_restore(void)
{
    if (!raw_mode_enabled)
        return;

    /*
     * TCSAFLUSH descarta bytes de entrada que ainda não foram processados.
     * Isso evita que teclas pressionadas no editor apareçam no shell.
     */
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_terminal) == -1)
        perror("tcsetattr: failed to restore terminal");

    raw_mode_enabled = false;
}

bool
terminal_enable_raw_mode(void)
{
    if (raw_mode_enabled)
        return true;

    if (!isatty(STDIN_FILENO))
    {
        fprintf(stderr, "standard input is not a terminal\n");
        return false;
    }

    if (tcgetattr(STDIN_FILENO, &original_terminal) == -1)
    {
        perror("tcgetattr");
        return false;
    }

    struct termios raw = original_terminal;

    /*
     * Input flags.
     *
     * BRKINT  - não transforma break em SIGINT.
     * ICRNL   - não transforma Enter (\r) em newline (\n).
     * INPCK   - desativa verificação de paridade.
     * ISTRIP  - não remove o oitavo bit dos bytes.
     * IXON    - desativa Ctrl+S e Ctrl+Q como controle de fluxo.
     */
    raw.c_iflag &= (tcflag_t) ~(BRKINT |
                               ICRNL  |
                               INPCK  |
                               ISTRIP |
                               IXON);

    /*
     * Output flags.
     *
     * OPOST desativa transformações de saída, como converter '\n'
     * automaticamente em "\r\n".
     */
    raw.c_oflag &= (tcflag_t) ~OPOST;

    /*
     * Control flags.
     *
     * CS8 configura caracteres de 8 bits.
     */
    raw.c_cflag |= CS8;

    /*
     * Local flags.
     *
     * ECHO   - não mostra as teclas pressionadas.
     * ICANON - entrega bytes imediatamente, sem esperar Enter.
     * IEXTEN - desativa processamento especial, como Ctrl+V.
     *
     * ISIG foi mantido propositalmente. Assim Ctrl+C, Ctrl+Z e Ctrl+\
     * continuam gerando sinais.
     */
    raw.c_lflag &= (tcflag_t) ~(ECHO |
                               ICANON |
                               IEXTEN);

    /*
     * read() retorna quando:
     *
     * - pelo menos um byte estiver disponível; ou
     * - passarem 100 ms sem receber nenhum byte.
     *
     * VTIME é medido em décimos de segundo.
     */
    raw.c_cc[VMIN]  = 0;
    raw.c_cc[VTIME] = 1;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
    {
        perror("tcsetattr: failed to enable raw mode");
        return false;
    }

    raw_mode_enabled = true;

    if (atexit(terminal_restore) != 0)
    {
        fprintf(stderr, "failed to register terminal restoration\n");
        terminal_restore();
        return false;
    }

    return true;
}

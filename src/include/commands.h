#ifndef __COMMANDS_H
#define __COMMANDS_H

void ping(struct discord *client, const struct discord_interaction *event);
void get_neko(struct discord *client, const struct discord_interaction *event, const char *endpoint);

#endif /* __COMMANDS_H */
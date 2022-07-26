#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <concord/discord.h>

#include <commands.h>

void on_ready(struct discord *client, const struct discord_ready *event) {
    struct discord_create_guild_application_command ping = {
        .name = "ping",
        .description = "Show the bot's latency"
    };

    struct discord_create_guild_application_command neko = {
        .name = "neko",
        .description = "Show an image of a neko"
    };

    for (int i = 0; i < event->guilds->size; i++) {
        discord_create_guild_application_command(
            client, event->application->id, event->guilds->array[i].id, &ping, NULL
        );

        discord_create_guild_application_command(
            client, event->application->id, event->guilds->array[i].id, &neko, NULL
        );
    }

    log_info("Logged in as %s#%s", event->user->username, event->user->discriminator);
}

void on_interaction(struct discord *client, const struct discord_interaction *event) {
    if (event->type != DISCORD_INTERACTION_APPLICATION_COMMAND)
        return;

    char *command_name = event->data->name;

    if (strcmp(command_name, "ping") == 0) {
        ping(client, event);
    } else if (strcmp(command_name, "neko") == 0) {
        neko(client, event);
    }
}

int main(void) {
    /* config file is relative to the executable */
    struct discord *client = discord_config_init("config.json");

    srand(time(NULL));

    discord_set_on_ready(client, &on_ready);
    discord_set_on_interaction_create(client, &on_interaction);
    discord_run(client);
}

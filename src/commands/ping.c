#include <concord/discord.h>

void ping(struct discord *client, const struct discord_interaction *event) {
    struct discord_interaction_response params = {
        .type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
        .data = &(struct discord_interaction_callback_data) {
            .content = NULL
        }
    };

    char buffer[64] = "";
    sprintf(buffer, "pong! :ping_pong: `%dms`", discord_get_ping(client));

    params.data->content = buffer;

    discord_create_interaction_response(client, event->id, event->token, &params, NULL);
}

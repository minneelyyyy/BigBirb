#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <json.h>
#include <nekos-life.h>
#include <concord/discord.h>

void neko(struct discord *client, const struct discord_interaction *event) {
    char *data = nekos_life_get("neko");
    char *url = data == NULL ? NULL : json_get_string_field("url", data, strlen(data));

    struct discord_interaction_response params = {
        .type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
        .data = &(struct discord_interaction_callback_data) {
            .content = data == NULL ? "Failed to get neko! API Error!" : url
        }
    };

    discord_create_interaction_response(client, event->id, event->token, &params, NULL);

    free(data);
    free(url);
}

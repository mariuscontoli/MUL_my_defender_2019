/*
** EPITECH PROJECT, 2020
** MUL_my_defender_2019
** File description:
** Init_play_scene
*/

#include "../../include/my_defender.h"

void i_hud(play_scene *scene)
{
    scene->background.sprite = sfSprite_create();
    scene->background.texture = sfTexture_createFromFile("img/play_scene/in_game/game_hud.png", NULL);
    scene->background.pos = (sfVector2f){0.0, 0.0};
    sfSprite_setPosition(scene->background.sprite, scene->background.pos);
    sfSprite_setTexture(scene->background.sprite, scene->background.texture,
    sfTrue);
    scene->pause_btn = create_button("img/in_game_buttons/settings_",
    (sfFloatRect){1454, 891, 75, 75});
}

void fill_map_texture(play_scene *play_scene)
{
    switch (play_scene->map.map_index) {
        case 1 : sfSprite_setTexture(play_scene->map.sprite,    play_scene->map.texture_one, sfTrue);
            break;
        case 2 : sfSprite_setTexture(play_scene->map.sprite,    play_scene->map.texture_two, sfTrue);
            break;
        case 3 : sfSprite_setTexture(play_scene->map.sprite,    play_scene->map.texture_three, sfTrue);
            break;
        default : break;
    }
}

void i_map(play_scene *play_scene)
{
    play_scene->map.sprite = sfSprite_create();
    play_scene->map.pos = (sfVector2f){235, 0};
    play_scene->difficulty = NORMAL;
    play_scene->map.map_index = 0;
    play_scene->map.coord = malloc(sizeof(coord));
    play_scene->map.coord->index = -1;
    play_scene->map.texture_one = sfTexture_createFromFile("img/play_scene/maps/map1.png", NULL);
    play_scene->map.texture_two = sfTexture_createFromFile("img/play_scene/maps/map2.png", NULL);
    play_scene->map.texture_three = sfTexture_createFromFile("img/play_scene/maps/map3.png", NULL);
    sfSprite_setPosition(play_scene->map.sprite, play_scene->map.pos);
}

void set_difficulty(play_scene *play_scene)
{
    switch (play_scene->difficulty) {
        case EASY : play_scene->player_infos.health = 150;
            break;
        case NORMAL : play_scene->player_infos.health = 100;
            break;
        case HARD : play_scene->player_infos.health = 50;
            break;
    }
}

void set_money(play_scene *play_scene)
{
    play_scene->player_infos.money = 1000;
}

void set_texts(play_scene *play_scene)
{
    play_scene->player_infos.money_text = sfText_create();
    play_scene->player_infos.health_text = sfText_create();
    sfText_setPosition(play_scene->player_infos.money_text, (sfVector2f){1580, 56});
    sfText_setPosition(play_scene->player_infos.health_text, (sfVector2f){1580, 120});
    sfText_setString(play_scene->player_infos.money_text, my_itoa
    (play_scene->player_infos.money, play_scene->player_infos.money_str));
    sfText_setString(play_scene->player_infos.health_text, my_itoa
    (play_scene->player_infos.health, play_scene->player_infos.health_str));
}

void set_turret_node(play_scene *scene)
{
    scene->turrets_placed.texture = sfTexture_createFromFile("img/play_scene/towers/turrets.png", NULL);
    scene->turrets_placed.turrets = malloc(sizeof(turret_t));
    scene->turrets_placed.turrets->range = -1;
}

int set_enemy_health(int type)
{
    switch (type) {
        case 1 : return (1);
        case 2 : return (2);
        case 3 : return (3);
        case 4 : return (4);
        case 5 : return (5);
        case 6 : return (6);
        case 7 : return (7);
        case 8 : return (8);
        default : return (1);
    }
}

void set_txt_en_rect(sfSprite *sprite, sfTexture *texture, sfIntRect rect)
{
    sfSprite_setTexture(sprite, texture, sfFalse);
    sfSprite_setTextureRect(sprite, rect);
}

void set_texture_enemy(sfSprite *sprite, sfTexture *texture, int e_list)
{
    switch (e_list) {
        case 1 : set_txt_en_rect(sprite, texture, (sfIntRect){0, 0, 49, 65});
            break;
        case 2 : set_txt_en_rect(sprite, texture, (sfIntRect){49, 0, 50, 65});
            break;
        case 3 : set_txt_en_rect(sprite, texture, (sfIntRect){99, 0, 49, 65});
            break;
        case 4 : set_txt_en_rect(sprite, texture, (sfIntRect){148, 0, 49, 65});
            break;
        case 5 : set_txt_en_rect(sprite, texture, (sfIntRect){197, 0, 49, 65});
            break;
        case 6 : set_txt_en_rect(sprite, texture, (sfIntRect){246, 0, 50, 65});
            break;
        case 7 : set_txt_en_rect(sprite, texture, (sfIntRect){296, 0, 49, 65});
            break;
        case 8 : set_txt_en_rect(sprite, texture, (sfIntRect){345, 0, 49, 65});
            break;
    }
}

void add_enemy_node(play_scene *scene, int *e_list, int index)
{
    printf("\tEnemy n°%d, of type %d\n", index, e_list[index]);
    if (scene->waves->enemy->health == -1) {
        scene->waves->enemy->sprite = sfSprite_create();
        scene->waves->enemy->hitbox = (sfIntRect){0, 0, 49, 65};
        set_texture_enemy(scene->waves->enemy->sprite, scene->waves->texture, e_list[index]);
        sfSprite_setOrigin(scene->waves->enemy->sprite, (sfVector2f){49 / 2, 65 / 2});
        scene->waves->enemy->pos = (sfVector2f){-1000, -1000};
        scene->waves->enemy->hitbox = (sfIntRect){0, 0, 49, 65};
        scene->waves->enemy->type = e_list[index];
        scene->waves->enemy->health = set_enemy_health(e_list[index]);
        scene->waves->enemy->previous = NULL;
        scene->waves->enemy->next = NULL;
    }
    else {
        while (scene->waves->enemy->next != NULL)
            scene->waves->enemy = scene->waves->enemy->next;
        enemy_t *temp = malloc(sizeof(enemy_t));
        temp->sprite = sfSprite_create();
        set_texture_enemy(temp->sprite, scene->waves->texture, e_list[index]);
        sfSprite_setOrigin(temp->sprite, (sfVector2f){49 / 2, 65 / 2});
        temp->pos = (sfVector2f){-1000, -1000};
        temp->hitbox = (sfIntRect){0, 0, 49, 65};
        temp->type = e_list[index];
        temp->health = set_enemy_health(e_list[index]);
        scene->waves->enemy->next = temp;
        temp->previous = scene->waves->enemy;
        temp->next = NULL;
    }
}

void add_wave_node(play_scene *scene, int index, int *e_list)
{
    printf("Index n°%d\n", index);
    if (scene->waves->index == -1) {
        scene->waves->index = index;
        scene->waves->texture = scene->enemy_texture;
        for (int i = 0; i < 10; i++)
            add_enemy_node(scene, e_list, i);
        scene->waves->previous = NULL;
        scene->waves->next = NULL;
    }
    else {
        while (scene->waves->next != NULL)
            scene->waves = scene->waves->next;
        wave_t *temp = malloc(sizeof(wave_t));
        temp->enemy = malloc(sizeof(enemy_t));
        temp->enemy->health = -1;
        temp->index = index;
        temp->texture = scene->enemy_texture;
        for (int i = 0; i < 10; i++)
            add_enemy_node(scene, e_list, i);
        scene->waves->next = temp;
        temp->previous = scene->waves;
        temp->next = NULL;
    }
}

void set_waves(play_scene *scene)
{
    int wave_nb = 10;
    int enemy_list[10][10] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, {3, 3, 3, 3, 3, 3, 3, 3, 3, 3}, {4, 4, 4, 4, 4, 4, 4, 4, 4, 4}, {5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, {6, 6, 6, 6, 6, 6, 6, 6, 6, 6}, {7, 7, 7, 7, 7, 7, 7, 7, 7, 7}, {8, 8, 8, 8, 8, 8, 8, 8, 8, 8}, {8, 8, 8, 8, 8, 8, 8, 8, 8, 8}, {8, 8, 8, 8, 8, 8, 8, 8, 8, 8}};
    for (int i = 0; i < wave_nb; i++) {
        printf("Wave n°%d\n", i);
        add_wave_node(scene, i, enemy_list[i]);
    }
}

void set_waves_positions(play_scene *scene)
{

}

void i_pause_menu(play_scene *scene)
{
    scene->pause_menu.background = set_simple_entity("img/play_scene/in_game/pause_menu.png", (sfFloatRect){700, 125, 447, 634});
    scene->pause_menu.resume = create_button("img/buttons/resume_", (sfFloatRect){760, 300, 314, 82});
    scene->pause_menu.restart = create_button("img/buttons/restart_", (sfFloatRect){760, 400, 314, 82});
    scene->pause_menu.main_menu = create_button("img/buttons/mainmenu_", (sfFloatRect){760, 500, 314, 82});
    scene->pause_menu.quit = create_button("img/buttons/quit_", (sfFloatRect){760, 600, 314, 82});
}

void i_wave_index(play_scene *scene)
{
    scene->waves = malloc(sizeof(wave_t));
    scene->waves->index = -1;
    scene->waves->enemy = malloc(sizeof(enemy_t));
    scene->waves->enemy->health = -1;
    scene->enemy_texture = sfTexture_createFromFile("img/play_scene/enemies/enemies.png", NULL);
    scene->waves->texture = scene->enemy_texture;
}

void i_play_scene(play_scene *play_scene, sfRenderWindow *window)
{
    play_scene->window = window;
    i_hud(play_scene);
    i_map(play_scene);
    i_turrets_price(play_scene);
    i_turret_hud(play_scene);
    i_dragndrop(play_scene);
    i_pause_menu(play_scene);
    i_wave_index(play_scene);
}

void set_play_values(play_scene *play_scene)
{
    play_scene->general_clock = sfClock_create();
    play_scene->pause_state = 0;
    fill_map_texture(play_scene);
    set_map_coord(&play_scene->map);
    i_player_infos(play_scene);
    i_font(play_scene);
    set_turret_node(play_scene);
    set_waves(play_scene);
    set_waves_positions(play_scene);
}
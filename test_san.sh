# Посылаем 20 запросов параллельно
for i in {1..20}; do
    ./build/calculator_client \
        '{"mode":"calculation","first_num":5,"second_num":2,"operation":"+"}' &
done
wait

# Разные операции одновременно
./build/calculator_client '{"mode":"calculation","first_num":10,"second_num":2,"operation":"+"}' &
./build/calculator_client '{"mode":"calculation","first_num":10,"second_num":2,"operation":"*"}' &
./build/calculator_client '{"mode":"calculation","first_num":10,"second_num":2,"operation":"-"}' &
./build/calculator_client '{"mode":"calculation","first_num":10,"second_num":0,"operation":"/"}' &
wait
# Clock Services

Depends on Extended Event Queues, as we post events for key things (e.g., 1-ms heartbeat tic).


for PC, requires continual polling as quickly as possible
for embedded, relies on a 1ms clock tic

because of this difference in operational modes, depends on board (which in turn depends on arch)
